// Shared C++ Inbox filtering; JavaScript never implements a parallel message list.
import fs from 'node:fs';
import path from 'node:path';
import {pathToFileURL} from 'node:url';
import {execFileSync} from 'node:child_process';
import crypto from 'node:crypto';
import assert from 'node:assert/strict';
const channels=['public','test','lu-alert','trafic','luxembourg','hammradio','bot','emergency','saarland','trier'].map(name=>'#'+name);
const {default:createSimulator}=await import(pathToFileURL(path.resolve('docs/simulator/wasm/core.mjs')));
const core=await createSimulator({wasmBinary:fs.readFileSync('docs/simulator/wasm/core.wasm')});core._sim_init();
assert.equal(core._sim_input_profile(),0);assert.equal(core._sim_rx_channel_count(),10);
assert.deepEqual(Array.from({length:core._sim_rx_channel_count()},(_,n)=>core.UTF8ToString(core._sim_rx_channel_name(n))),channels);
assert.deepEqual(Array.from({length:core._sim_channel_count()},(_,n)=>core.UTF8ToString(core._sim_channel_name(n))),channels);
assert.equal(core._sim_rx_filter(),-1);assert.equal(core._sim_sends(),0);
const commands=[],checks=new Map(),labels=new Map();
const add=(op,a=0,check,label)=>{commands.push([op,a]);if(check)checks.set(commands.length-1,check);if(label)labels.set(commands.length-1,label);};
const noTx=({state})=>assert.equal(state[5],0),key=n=>add('key',n),step=n=>add('step',n),triple=()=>{key(27);step(120);key(27);step(120);key(27);};
add('init');add('rx_demo',0,noTx,'all-before');
for(let n=0;n<10;n++)add('rx_filter',n,({rx,state})=>{assert.equal(rx[0],n);assert.ok(rx[1]>=0&&rx[1]<=8);assert.equal(state[5],0);},'filter-'+n);
add('rx_filter',-1,({rx})=>assert.equal(rx[0],-1),'all-after');
// Enter, Down and Enter follow the same on-device channel chooser path.
key(13);add('step',0,noTx,'physical-chooser');key(182);add('key',13,({rx})=>assert.equal(rx[0],0),'physical-public');
// Lock guards both local filter shortcuts and synthetic demo injection.
add('rx_filter',3);triple();add('step',500,({state})=>assert.equal(state[3],1),'locked');
add('rx_filter',5,({rx,state})=>{assert.equal(state[3],1);assert.equal(rx[0],3);assert.equal(state[5],0);});
add('rx_demo',0,({rx,state})=>{assert.equal(state[3],1);assert.equal(rx[0],3);assert.equal(state[5],0);},'locked-demo');
triple();add('step',750,({state,rx})=>{assert.equal(state[3],0);assert.equal(rx[0],3);assert.equal(state[5],0);});
add('rx_filter',-1,noTx,'all-unlocked');
const native=execFileSync('./build/web/native-oracle',{input:commands.map(([op,a])=>`${op} ${a}`).join('\n')+'\n',encoding:'utf8',maxBuffer:64*1024*1024}).trim().split('\n').map(JSON.parse),meta=native.shift();
assert.deepEqual(meta.channels.map(c=>c.name),channels);for(let n=0;n<10;n++){assert.ok(core._sim_preset_count(n)>0);for(let k=0;k<core._sim_preset_count(n);k++)assert.ok(!/cfl-info|saarloorlux/i.test(core.UTF8ToString(core._sim_preset_text(n,k))));}
assert.equal(native.length,commands.length);
const snapshots=new Map();let groups=5;
for(let n=0;n<commands.length;n++){
 const[op,a]=commands[n];({init:()=>core._sim_init(),rx_demo:()=>core._sim_rx_demo(),rx_filter:()=>core._sim_rx_set_filter(a),key:()=>core._sim_key(a),step:()=>core._sim_step(a)})[op]();
 const ptr=core._sim_frame(),pixels=Buffer.from(core.HEAPU8.subarray(ptr,ptr+1024));
 const state=[core._sim_page(),core._sim_pet(),core._sim_picker(),core._sim_locked(),core._sim_sound(),core._sim_sends(),core._sim_rx(),core._sim_utc(),core._sim_local(),core._sim_overflows(),core._sim_quick_page()],rx=[core._sim_rx_filter(),core._sim_rx_visible_count()];
 assert.deepEqual(state,native[n].state,`Native/WASM state ${n}: ${op}`);assert.deepEqual(rx,native[n].rx,`Native/WASM RX state ${n}: ${op}`);assert.equal(pixels.toString('hex'),native[n].frame,`Native/WASM pixels ${n}: ${op}`);assert.equal(state[9],0);assert.equal(state[5],0);
 if(checks.has(n)){checks.get(n)({state,rx});groups++;}if(labels.has(n))snapshots.set(labels.get(n),{pixels,state,rx});
}
const before=snapshots.get('all-before'),after=snapshots.get('all-after');assert.equal(before.rx[1],8);assert.equal(after.rx[1],before.rx[1]);
assert.equal(Array.from({length:10},(_,n)=>snapshots.get('filter-'+n).rx[1]).reduce((a,b)=>a+b,0),before.rx[1]);
assert.notEqual(snapshots.get('physical-chooser').pixels.toString('hex'),after.pixels.toString('hex'));assert.deepEqual(snapshots.get('locked-demo').pixels,snapshots.get('locked').pixels);groups+=4;
const report={result:'PASS',scope:'LU-Alert Wio shared C++ RX channel chooser and filter',channel_names:channels,channel_count:10,native_wasm_framebuffer_comparisons:commands.length,functional_groups:groups,all_visible_count:before.rx[1],filter_counts:channels.map((name,n)=>({name,count:snapshots.get('filter-'+n).rx[1]})),device_access:false,hardware_flashed:false,wasm_sha256:crypto.createHash('sha256').update(fs.readFileSync('docs/simulator/wasm/core.wasm')).digest('hex')};
fs.mkdirSync('build/rx-channels-web',{recursive:true});fs.writeFileSync('build/rx-channels-web/RESULTS.json',JSON.stringify(report,null,2)+'\n');fs.writeFileSync('docs/simulator/RX-CHANNELS-TEST-RESULT.json',JSON.stringify(report,null,2)+'\n');
const manifest=JSON.parse(fs.readFileSync('docs/simulator/BUILD-MANIFEST.json','utf8'));manifest.rx_channel_tests=report;fs.writeFileSync('docs/simulator/BUILD-MANIFEST.json',JSON.stringify(manifest,null,2)+'\n');console.log(JSON.stringify(report));
