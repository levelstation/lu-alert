const pages={
 first:{src:'assets/wio-channels-1.png',names:'#public, #test, #lu-alert, #trafic',number:1},
 second:{src:'assets/wio-channels-2.png',names:'#luxembourg, #hammradio, #bot, #emergency',number:2},
 third:{src:'assets/wio-channels-3.png',names:'#saarland, #trier',number:3}
};
const buttons=[...document.querySelectorAll('[data-page]')];
const frame=document.querySelector('#channel-frame');
const caption=document.querySelector('#channel-caption');
for(const button of buttons)button.addEventListener('click',()=>{
 const page=pages[button.dataset.page];if(!page||!frame||!caption)return;
 frame.src=page.src;frame.alt='Wio Quick TX, Seite '+page.number+': '+page.names;
 caption.textContent='Quick TX · Seite '+page.number+' von 3 · '+page.names;
 for(const item of buttons){item.classList.toggle('selected',item===button);item.setAttribute('aria-pressed',String(item===button));}
});
