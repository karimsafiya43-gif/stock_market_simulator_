const $=(s,r=document)=>r.querySelector(s);
const inr=n=>'₹'+Number(n).toLocaleString('en-IN',{minimumFractionDigits:2,maximumFractionDigits:2});
const inr0=n=>'₹'+Math.round(n).toLocaleString('en-IN');
const pct=n=>(n>=0?'+':'')+n.toFixed(2)+'%';const cls=n=>n>=0?'up':'down';
const get=(k,d)=>{try{const v=JSON.parse(localStorage.getItem(k));return v??d}catch{return d}};
const set=(k,v)=>localStorage.setItem(k,JSON.stringify(v));
const find=s=>STOCKS.find(x=>x.sym===s)||STOCKS[0];
const q=new URLSearchParams(location.search);
const P={home:'<path d="M3 10.5 12 3l9 7.5V20a1 1 0 0 1-1 1h-5v-6H9v6H4a1 1 0 0 1-1-1z"/>',
discover:'<circle cx="12" cy="12" r="9"/><path d="m15.5 8.5-2 5-5 2 2-5z"/>',
portfolio:'<path d="M21 12A9 9 0 1 1 12 3v9z"/><path d="M15 3.5A9 9 0 0 1 20.5 9H15z"/>',
watchlist:'<path d="m12 3 2.7 5.6 6.1.9-4.4 4.3 1 6.1L12 17l-5.4 2.9 1-6.1L3.2 9.5l6.1-.9z"/>',
activity:'<path d="M8 6h13M8 12h13M8 18h13M3 6h.01M3 12h.01M3 18h.01"/>',
leaderboard:'<path d="M8 21h8M12 17v4M7 4h10v5a5 5 0 0 1-10 0zM7 6H4v1a3 3 0 0 0 3 3M17 6h3v1a3 3 0 0 1-3 3"/>',
learn:'<path d="M4 4.5A2.5 2.5 0 0 1 6.5 2H20v17H6.5A2.5 2.5 0 0 0 4 21.5z"/><path d="M4 19.5A2.5 2.5 0 0 1 6.5 17H20"/>',
wallet:'<path d="M3 7a2 2 0 0 1 2-2h13v4"/><path d="M3 7v11a2 2 0 0 0 2 2h15V9H5a2 2 0 0 1-2-2z"/><circle cx="16.5" cy="14.5" r="1"/>',
trend:'<path d="m3 17 6-6 4 4 8-8"/><path d="M15 7h6v6"/>',
layers:'<path d="m12 3 9 5-9 5-9-5z"/><path d="m3 13 9 5 9-5"/>'};
const I=n=>`<svg class="ic" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">${P[n]}</svg>`;
function get_t(){try{return JSON.parse(sessionStorage.getItem('ss_trade'))}catch{return null}}

function spark(d,fill,cn='spark'){const w=300,h=60,mn=Math.min(...d),mx=Math.max(...d);
 const L=d.map((v,i)=>(i?'L':'M')+(i/(d.length-1)*w).toFixed(1)+' '+(h-3-(v-mn)/(mx-mn||1)*(h-6)).toFixed(1)).join('');
 const c=d[d.length-1]>=d[0]?'var(--up)':'var(--down)';
 return `<svg class="${cn}" viewBox="0 0 ${w} ${h}" preserveAspectRatio="none">${fill?`<path d="${L}L${w} ${h}L0 ${h}Z" fill="${c}" opacity=".15"/>`:''}<path d="${L}" fill="none" stroke="${c}" stroke-width="2" stroke-linejoin="round" vector-effect="non-scaling-stroke"/></svg>`}
const card=s=>`<a class="card sc" href="stock.html?s=${s.sym}"><div class="sc-top"><div><div class="sym">${s.sym}</div><div class="nm">${s.name}</div></div><span class="pill ${cls(s.chg)}">${pct(s.chg)}</span></div><div class="price">${inr(s.price)}</div>${spark(s.data)}</a>`;
const stat=(l,v,c='',ic='wallet')=>`<div class="card stat"><span class="ico">${I(ic)}</span><small>${l}</small><b class="${c}">${v}</b></div>`;
const head=(t,p,x='')=>`<div class="head"><div><h1>${t}</h1><p>${p}</p></div>${x}</div>`;
const txns=()=>[...get('ss_txns',[]),...TXNS];
const holdings=()=>{const m={};HOLDINGS.forEach(h=>m[h.sym]={...h});
 get('ss_txns',[]).slice().reverse().forEach(t=>{const h=m[t.sym]||(m[t.sym]={sym:t.sym,qty:0,avg:0});
  if(t.side==='BUY'){h.avg=(h.avg*h.qty+t.price*t.qty)/(h.qty+t.qty);h.qty+=t.qty}else h.qty-=t.qty});
 return Object.values(m).filter(h=>h.qty>0)};
const cash=()=>get('ss_cash',USER.balance);
const invested=()=>holdings().reduce((a,h)=>a+h.qty*find(h.sym).price,0);
const plTotal=()=>holdings().reduce((a,h)=>a+h.qty*(find(h.sym).price-h.avg),0);
const toast=m=>{const t=document.createElement('div');t.className='toast';t.textContent=m;document.body.append(t);setTimeout(()=>t.remove(),2000)};

const LINKS=[['home','Home'],['discover','Discover'],['portfolio','Portfolio'],['watchlist','Watchlist'],['activity','Activity'],['leaderboard','Leaderboard'],['learn','Learn']];
function nav(p){const t=STOCKS.map(s=>`<span>${s.sym} <b class="${cls(s.chg)}">${pct(s.chg)}</b></span>`).join('');
 return `<header class="nav"><div class="nav-in"><a class="logo" href="home.html"><i>${I('trend')}</i>StockSim</a><nav class="links">${LINKS.map(([k,l])=>`<a href="${k}.html" class="${p===k?'on':''}">${I(k)}${l}</a>`).join('')}</nav><a href="profile.html" class="avatar" title="Profile">${USER.name[0]}</a></div><div class="ticker"><div class="ticker-t">${t}${t}</div></div></header>`}

const authArt=`<div class="auth-art"><a class="logo" href="login.html"><i>${I('trend')}</i>StockSim</a><div><h1>Practice investing.<br>Zero risk, real learning.</h1><p style="margin-top:14px;max-width:380px">₹10,00,000 virtual cash se shuru karo, trades lagao aur leaderboard pe chadho.</p></div>${spark(STOCKS[6].data,true)}<span class="muted">Virtual money only. Koi real paisa involve nahi.</span></div>`;
const authForm=(t,sub,fields,btn,alt)=>`<div class="auth">${authArt}<div class="auth-form"><form id="af"><h1 style="font-size:2rem">${t}</h1><p>${sub}</p>${fields}<button class="btn full" style="margin-top:22px">${btn}</button><p style="margin-top:18px;text-align:center">${alt}</p></form></div></div>`;
const f=(l,t,n,ph='',x='')=>`<label for="${n}">${l}</label><input id="${n}" type="${t}" placeholder="${ph}" ${x} required>`;

const R={
login:()=>authForm('Welcome back','Apne account mein login karo.',f('Email','email','em','you@example.com')+f('Password','password','pw'),'Log in','Naye ho? <a class="up" href="signup.html">Create an account</a>'),
signup:()=>authForm('Create your account','Free hai, 30 second lagenge.',f('Full name','text','nm','Safiya Karim')+f('Email','email','em','you@example.com')+f('Password','password','pw','Min 8 characters'),'Start with ₹10,00,000','Already have an account? <a class="up" href="login.html">Log in</a>'),
home(){const pv=invested(),tot=pv+cash(),pl=plTotal(),mv=[...STOCKS].sort((a,b)=>b.chg-a.chg);
 return `<div class="hero"><p>Namaste, ${USER.name.split(' ')[0]}. Aapka net worth</p><div class="big">${inr0(tot)}</div><span class="pill ${cls(pl)}">${pl>=0?'▲':'▼'} ${inr0(Math.abs(pl))} overall P&amp;L</span><div style="margin-top:22px;display:flex;gap:10px;flex-wrap:wrap"><a class="btn" href="discover.html">${I('discover')}Find a stock</a><a class="btn ghost" href="portfolio.html">View portfolio</a></div>${spark(STOCKS[0].data,true)}</div>
 <div class="grid g4 sec">${stat('Cash available',inr0(cash()),'','wallet')}${stat('Invested',inr0(pv),'','trend')}${stat('Holdings',holdings().length+' stocks','','layers')}${stat('Leaderboard rank','#3','up','leaderboard')}</div>
 <div class="sec"><h2>Top gainers today</h2><div class="grid g4">${mv.slice(0,4).map(card).join('')}</div></div>
 <div class="sec"><h2>Biggest drops</h2><div class="grid g4">${mv.slice(-4).reverse().map(card).join('')}</div></div>`},
discover(){const secs=['All',...new Set(STOCKS.map(s=>s.sector))];
 setTimeout(()=>{const draw=()=>{const k=$('#sq').value.toLowerCase(),c=$('.chip.on').dataset.s;
  const l=STOCKS.filter(s=>(c==='All'||s.sector===c)&&(s.sym+s.name).toLowerCase().includes(k));
  $('#dg').innerHTML=l.map(card).join('')||'<p>Koi stock nahi mila. Alag naam try karo.</p>'};
  $('#sq').oninput=draw;document.querySelectorAll('.chip').forEach(b=>b.onclick=()=>{$('.chip.on').classList.remove('on');b.classList.add('on');draw()});draw()});
 return head('Discover','Market mein se apna agla stock dhoondho.')+`<input id="sq" placeholder="Search by name or symbol">
 <div class="chips">${secs.map((s,i)=>`<button class="chip ${i?'':'on'}" data-s="${s}">${s}</button>`).join('')}</div><div class="grid g4" id="dg"></div>`},
stock(){const s=find(q.get('s')),w=get('ss_watch',['TCS','ZOMATO','ITC']);let side='BUY';
 setTimeout(()=>{const upd=()=>{$('#tot').textContent=inr((+$('#qty').value||0)*s.price)};$('#qty').oninput=upd;upd();
  document.querySelectorAll('.seg button').forEach(b=>b.onclick=()=>{side=b.dataset.v;document.querySelectorAll('.seg button').forEach(x=>x.className=x===b?'on '+(side==='BUY'?'b':'s'):'');
   const g=$('#go');g.className='btn full '+(side==='BUY'?'buy':'sell');g.textContent='Review '+side.toLowerCase()+' order'});
  $('#tf').onsubmit=e=>{e.preventDefault();sessionStorage.setItem('ss_trade',JSON.stringify({sym:s.sym,side,qty:+$('#qty').value,price:s.price}));location.href='trade_review.html'};
  $('#star').onclick=()=>{const l=get('ss_watch',w),i=l.indexOf(s.sym);i<0?l.push(s.sym):l.splice(i,1);set('ss_watch',l);$('#star').textContent=i<0?'★ Watching':'☆ Add to watchlist';toast(i<0?'Added to watchlist':'Removed from watchlist')}});
 return `<a class="muted" href="discover.html">← Back to discover</a><div style="height:14px"></div>${head(s.name+' ('+s.sym+')',s.sector,`<button class="btn ghost" id="star">${w.includes(s.sym)?'★ Watching':'☆ Add to watchlist'}</button>`)}
 <div class="grid" style="grid-template-columns:repeat(auto-fit,minmax(300px,1fr))"><div class="card chart-box" style="grid-column:span 2;min-width:0"><div style="padding:8px 12px"><div class="price" style="font-size:2rem;margin:0">${inr(s.price)}</div><span class="pill ${cls(s.chg)}">${pct(s.chg)} today</span></div>${spark(s.data,true,'chart')}</div>
 <form class="card" id="tf"><h2>Place an order</h2><div class="seg" style="margin-top:14px"><button type="button" data-v="BUY" class="on b">Buy</button><button type="button" data-v="SELL">Sell</button></div>${f('Quantity','number','qty','1','min="1" value="1"')}<div class="row"><span class="muted">Estimated total</span><b id="tot"></b></div><button class="btn buy full" id="go" style="margin-top:8px">Review buy order</button></form></div>`},
trade_review(){const t=get_t();if(!t)return R.error();const sub=t.qty*t.price,fee=sub*.001,tot=t.side==='BUY'?sub+fee:sub-fee;
 setTimeout(()=>$('#ok').onclick=()=>{if(t.side==='BUY'&&tot>cash())return toast('Cash kam hai');
  set('ss_txns',[{id:Date.now()%100000,side:t.side,sym:t.sym,qty:t.qty,price:t.price,date:new Date().toLocaleDateString('en-GB',{day:'2-digit',month:'short',year:'numeric'})},...get('ss_txns',[])]);
  set('ss_cash',cash()+(t.side==='BUY'?-tot:tot));location.href='trade_done.html'});
 return `<div class="center" style="text-align:left"><h1>Review your order</h1><p style="margin:6px 0 20px">Confirm karne se pehle ek baar dekh lo.</p><div class="card"><div class="row"><span class="muted">Action</span><b class="${t.side==='BUY'?'up':'down'}">${t.side}</b></div><div class="row"><span class="muted">Stock</span><b>${t.sym}</b></div><div class="row"><span class="muted">Quantity</span><b>${t.qty}</b></div><div class="row"><span class="muted">Price per share</span><b>${inr(t.price)}</b></div><div class="row"><span class="muted">Fee (0.1%)</span><b>${inr(fee)}</b></div><div class="row"><span>Total</span><b style="font-size:1.3rem">${inr(tot)}</b></div></div><div style="display:flex;gap:10px;margin-top:18px"><a class="btn ghost" href="stock.html?s=${t.sym}">Edit</a><button class="btn full ${t.side==='BUY'?'buy':'sell'}" id="ok">Confirm ${t.side.toLowerCase()}</button></div></div>`},
trade_done(){const t=get_t();return `<div class="center"><div class="tick">✓</div><h1>Order placed</h1><p style="margin:10px 0 26px">${t?`${t.side==='BUY'?'Bought':'Sold'} ${t.qty} × ${t.sym} at ${inr(t.price)}.`:'Aapka order execute ho gaya.'}</p><div style="display:flex;gap:10px;justify-content:center"><a class="btn" href="portfolio.html">View portfolio</a><a class="btn ghost" href="discover.html">Keep exploring</a></div></div>`},
portfolio(){const H=holdings(),cols=['#ff9aa8','#b79cff','#6fd8b0','#ffcf6b','#7cc4ff'],tot=invested()||1;
 return head('Portfolio','Aapke saare holdings ek jagah.')+`<div class="grid g4">${stat('Current value',inr0(invested()),'','portfolio')}${stat('Cash',inr0(cash()),'','wallet')}${stat('Total P&L',inr0(plTotal()),cls(plTotal()),'trend')}</div>
 <div class="card sec"><h2>Allocation</h2><div class="bar">${H.map((h,i)=>`<span title="${h.sym}" style="width:${h.qty*find(h.sym).price/tot*100}%;background:${cols[i%5]}"></span>`).join('')}</div><div style="display:flex;gap:16px;flex-wrap:wrap">${H.map((h,i)=>`<span class="muted"><b style="color:${cols[i%5]}">●</b> ${h.sym}</span>`).join('')}</div></div>
 <div class="card sec tw"><table><tr><th>Stock</th><th class="r">Qty</th><th class="r">Avg price</th><th class="r">LTP</th><th class="r">P&amp;L</th></tr>${H.map(h=>{const s=find(h.sym),p=(s.price-h.avg)*h.qty;return `<tr><td><a href="stock.html?s=${s.sym}"><b>${s.sym}</b><br><span class="nm">${s.name}</span></a></td><td class="r">${h.qty}</td><td class="r">${inr(h.avg)}</td><td class="r">${inr(s.price)}</td><td class="r ${cls(p)}"><b>${inr0(p)}</b><br>${pct((s.price/h.avg-1)*100)}</td></tr>`}).join('')}</table></div>`},
watchlist(){const l=get('ss_watch',['TCS','ZOMATO','ITC']).map(find);
 return head('Watchlist','Jin stocks pe nazar rakhni hai.')+(l.length?`<div class="grid g3">${l.map(card).join('')}</div>`:`<div class="card center" style="margin:30px auto"><h2>Watchlist khaali hai</h2><p style="margin:8px 0 18px">Kisi stock ke page pe star dabake yahan add karo.</p><a class="btn" href="discover.html">Browse stocks</a></div>`)},
activity(){return head('Activity','Aapke saare buy aur sell orders.')+`<div class="card tw"><table><tr><th>Date</th><th>Type</th><th>Stock</th><th class="r">Qty</th><th class="r">Price</th><th class="r">Amount</th></tr>${txns().map(t=>`<tr><td class="muted">${t.date}</td><td><span class="pill ${t.side==='BUY'?'up':'down'}">${t.side}</span></td><td><b>${t.sym}</b></td><td class="r">${t.qty}</td><td class="r">${inr(t.price)}</td><td class="r"><b>${inr(t.qty*t.price)}</b></td></tr>`).join('')}</table></div>`},
leaderboard(){return head('Leaderboard','Is mahine ke top traders.')+`<div class="card">${BOARD.map((b,i)=>`<div class="row ${b.me?'me':''}"><div style="display:flex;gap:14px;align-items:center"><span class="rank ${i?'':'r1'}">${i+1}</span><div><b>${b.name}${b.me?' (you)':''}</b><br><span class="nm">${inr0(b.pv)}</span></div></div><b class="${cls(b.ret)}">${pct(b.ret)}</b></div>`).join('')}</div>`},
learn(){return head('Learn','Chhote lessons, seedhi bhasha mein.')+`<div class="grid g3">${LESSONS.map(l=>`<div class="card"><span class="pill">${l.m} read</span><h3 style="margin:14px 0 8px">${l.t}</h3><p>${l.d}</p></div>`).join('')}</div>`},
profile(){return head('Profile','Apne account ki details.')+`<div class="grid g2"><div class="card"><div style="display:flex;gap:16px;align-items:center"><span class="avatar" style="width:64px;height:64px;font-size:1.6rem">${USER.name[0]}</span><div><h2>${USER.name}</h2><p>@${USER.username}</p></div></div><div class="row" style="margin-top:18px"><span class="muted">Email</span><b>${USER.email}</b></div><div class="row"><span class="muted">Member since</span><b>${USER.joined}</b></div><div class="row"><span class="muted">Cash</span><b>${inr0(cash())}</b></div></div>
 <div class="card"><h2>Account</h2><p style="margin:8px 0 18px">Demo data reset karke dobara shuru karo.</p><button class="btn ghost" id="rs">Reset demo data</button> <a class="btn" href="login.html" style="margin-left:6px">Log out</a></div></div>`},
error:()=>`<div class="center"><h1 style="font-size:4rem">404</h1><h2 style="margin:8px 0">Ye page nahi mila</h2><p style="margin-bottom:24px">Link galat ho sakta hai ya page hata diya gaya hai.</p><a class="btn" href="home.html">Go to home</a></div>`};

const page=document.body.dataset.page,pub=['login','signup'].includes(page);
if(!pub)$('#nav').innerHTML=nav(page);
$('#app').innerHTML=R[page]();
if(pub){$('#app').className='';$('#af').onsubmit=e=>{e.preventDefault();location.href='home.html'}}
if($('#rs'))$('#rs').onclick=()=>{localStorage.clear();sessionStorage.clear();toast('Demo data reset ho gaya')};
