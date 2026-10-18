// Mock data: backend ready hone par real fetch() se replace karna
function series(seed,base,n=40){let x=seed,v=base*.9,o=[];for(let i=0;i<n;i++){x=(x*9301+49297)%233280;v+=(x/233280-.45)*base*.022;o.push(v)}const d=base-o[n-1];return o.map(v=>v+d)}
const _s=(sym,name,sector,price,chg,seed)=>({sym,name,sector,price,chg,data:series(seed,price)});
const STOCKS=[
 _s('RELIANCE','Reliance Industries','Energy',2874.5,1.24,11),_s('TCS','Tata Consultancy','IT',3921.1,-0.62,23),
 _s('INFY','Infosys','IT',1544.8,0.88,37),_s('HDFCBANK','HDFC Bank','Banking',1689.3,0.31,41),
 _s('ITC','ITC Limited','FMCG',468.2,-0.45,53),_s('TATAMOTORS','Tata Motors','Auto',972.6,2.17,67),
 _s('ZOMATO','Zomato','Consumer',238.9,3.42,71),_s('SBIN','State Bank of India','Banking',812.4,-1.08,83),
 _s('WIPRO','Wipro','IT',498.7,0.12,97),_s('ADANIENT','Adani Enterprises','Energy',2456.0,-2.31,101)];
const USER={name:'Safiya Karim',username:'safiya',email:'safiya@example.com',balance:742500,joined:'Oct 2026'};
const HOLDINGS=[{sym:'RELIANCE',qty:12,avg:2710},{sym:'TCS',qty:5,avg:3980},{sym:'ZOMATO',qty:150,avg:196.4},{sym:'ITC',qty:40,avg:451}];
const TXNS=[
 {id:1042,side:'BUY',sym:'ZOMATO',qty:50,price:231.2,date:'16 Oct 2026'},{id:1041,side:'SELL',sym:'INFY',qty:10,price:1532.0,date:'14 Oct 2026'},
 {id:1040,side:'BUY',sym:'RELIANCE',qty:12,price:2710.0,date:'11 Oct 2026'},{id:1039,side:'BUY',sym:'ITC',qty:40,price:451.0,date:'09 Oct 2026'},
 {id:1038,side:'BUY',sym:'TCS',qty:5,price:3980.0,date:'07 Oct 2026'}];
const BOARD=[{name:'Aarav Mehta',pv:1284000,ret:28.4},{name:'Diya Nair',pv:1196500,ret:19.6},{name:'Safiya Karim',pv:1122300,ret:12.2,me:1},
 {name:'Kabir Shah',pv:1087000,ret:8.7},{name:'Meera Iyer',pv:1041200,ret:4.1},{name:'Rohan Das',pv:968400,ret:-3.2}];
const LESSONS=[{t:'What is a stock?',d:'Ek company ka chhota sa hissa. Jab company badhti hai, aapka hissa bhi.',m:'3 min'},
 {t:'Reading a price chart',d:'Trend, support aur resistance ko pehchanna seekho.',m:'5 min'},
 {t:'Buy vs sell orders',d:'Market order aur limit order mein farak kya hai.',m:'4 min'},
 {t:'Diversification',d:'Sab ande ek tokri mein kyun nahi rakhte.',m:'4 min'},
 {t:'Risk and return',d:'Zyada return ke saath zyada risk bhi aata hai.',m:'6 min'},
 {t:'Reading your portfolio',d:'P&L, average price aur allocation samjho.',m:'5 min'}];
