const fs=require('node:fs'),vm=require('node:vm'),assert=require('node:assert/strict');
const html=fs.readFileSync('docs/index.html','utf8'),script=fs.readFileSync('docs/app.js','utf8');
for(const match of html.matchAll(/(?:src|href)="([^"]+)"/g)){const url=match[1].split('?')[0];if(url.startsWith('#')||url.startsWith('https:'))continue;assert(fs.existsSync('docs/'+url),'Missing '+url);}
const frame={},caption={};const buttons=['first','second'].map(page=>({dataset:{page},attrs:{},classList:{toggle(){}},setAttribute(k,v){this.attrs[k]=v},addEventListener(_,fn){this.click=fn}}));
vm.runInNewContext(script,{document:{querySelectorAll(){return buttons},querySelector(id){return id==='#channel-frame'?frame:caption}}});
buttons[1].click();assert.equal(frame.src,'assets/channels-second.png');assert.match(caption.textContent,/saarloorlux/);assert.equal(buttons[1].attrs['aria-pressed'],'true');buttons[0].click();assert.equal(frame.src,'assets/channels-first.png');assert.equal(buttons[1].attrs['aria-pressed'],'false');
assert(!/google-analytics|googletagmanager|localStorage|geolocation|document\.cookie/i.test(html+script));assert(!/cfl[- _]?info/i.test(html+script));
console.log('PASS: both channel pages, selection/ARIA state, all local assets/downloads, no tracking/location APIs');
