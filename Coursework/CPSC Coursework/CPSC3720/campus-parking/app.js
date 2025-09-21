// Simple, client-side demo. No backend. Simulates occupancy changes.

const map = L.map('map', { zoomControl: true }).setView([34.676, -82.84], 15);
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
  attribution: '&copy; OpenStreetMap'
}).addTo(map);

const typeFilterEl = document.getElementById('typeFilter');
const minOpenEl = document.getElementById('minOpen');
const lotListEl = document.getElementById('lotList');
const notifyToggle = document.getElementById('notifyToggle');
const locateBtn = document.getElementById('locateBtn');

let lots = [];
let markers = {};
let userLatLng = null;

function statusFor(open, capacity) {
  const ratio = open / capacity;
  if (ratio >= 0.3) return 'ok';
  if (ratio > 0.1) return 'warn';
  return 'bad';
}

function badgeText(s) {
  return s === 'ok' ? 'Good availability' : s === 'warn' ? 'Limited' : 'Nearly full';
}

function passesFilters(lot) {
  const typeOk = typeFilterEl.value === 'all' || lot.type === typeFilterEl.value;
  const openOk = lot.open >= Number(minOpenEl.value || 0);
  return typeOk && openOk;
}

function renderSidebar() {
  lotListEl.innerHTML = '';
  lots.filter(passesFilters).sort((a,b) => a.open - b.open).forEach(lot => {
    const s = statusFor(lot.open, lot.capacity);
    const li = document.createElement('li');
    li.className = 'lot';
    li.innerHTML = `
      <div class="row">
        <span class="dot ${s}"></span>
        <h3>${lot.name}</h3>
        <span class="badge">${lot.type}</span>
      </div>
      <div class="row">
        <span class="cap">${lot.open}/${lot.capacity} open</span>
        <span class="badge">${badgeText(s)}</span>
        <button data-pan="${lot.id}">Pan</button>
        <button data-nav="${lot.id}">Directions</button>
      </div>
    `;
    lotListEl.appendChild(li);
  });

  // Pan and directions handlers
  lotListEl.querySelectorAll('button[data-pan]').forEach(btn => {
    btn.onclick = () => {
      const lot = lots.find(l => l.id === btn.dataset.pan);
      map.setView([lot.lat, lot.lng], 17, { animate: true });
      markers[lot.id].openPopup();
    };
  });
  lotListEl.querySelectorAll('button[data-nav]').forEach(btn => {
    btn.onclick = () => {
      const lot = lots.find(l => l.id === btn.dataset.nav);
      const url = `https://www.google.com/maps/dir/?api=1&destination=${lot.lat},${lot.lng}`;
      window.open(url, '_blank');
    };
  });
}

function renderMarkers() {
  lots.forEach(lot => {
    const s = statusFor(lot.open, lot.capacity);
    const html = `
      <strong>${lot.name}</strong><br/>
      ${lot.open}/${lot.capacity} open<br/>
      <em>${badgeText(s)}</em>
    `;
    if (!markers[lot.id]) {
      markers[lot.id] = L.circleMarker([lot.lat, lot.lng], {
        radius: 10,
        color: s === 'ok' ? '#2e7d32' : s === 'warn' ? '#f9a825' : '#c62828',
        weight: 2,
        fillColor: '#000',
        fillOpacity: 0.2
      }).addTo(map).bindPopup(html);
    } else {
      markers[lot.id].setStyle({
        color: s === 'ok' ? '#2e7d32' : s === 'warn' ? '#f9a825' : '#c62828'
      });
      markers[lot.id].setPopupContent(html);
    }
    markers[lot.id].options.interactive = true;
  });
}

async function loadLots() {
  const res = await fetch('data/lots.json');
  lots = await res.json();
  renderMarkers();
  renderSidebar();
}

// Simulate occupancy changes every 8 seconds
function startSimulation() {
  setInterval(() => {
    lots.forEach(lot => {
      const delta = Math.floor((Math.random() * 10) - 5); // -5..+4
      lot.open = Math.max(0, Math.min(lot.capacity, lot.open + delta));
    });
    renderMarkers();
    renderSidebar();
    maybeNotify();
  }, 8000);
}

function distanceMeters(a, b) {
  const R = 6371000;
  const toRad = x => x * Math.PI / 180;
  const dLat = toRad(b.lat - a.lat), dLng = toRad(b.lng - a.lng);
  const sa = Math.sin(dLat/2) ** 2 + Math.cos(toRad(a.lat)) * Math.cos(toRad(b.lat)) * Math.sin(dLng/2) ** 2;
  return 2 * R * Math.asin(Math.sqrt(sa));
}

function maybeNotify() {
  if (!notifyToggle.checked || !userLatLng) return;
  const near = lots
    .filter(passesFilters)
    .filter(l => distanceMeters(userLatLng, {lat:l.lat, lng:l.lng}) < 600)
    .find(l => statusFor(l.open, l.capacity) !== 'bad');
  if (near) {
    // Simple in-page alert. If you want browser notifications, call Notification API.
    const msg = `Nearby lot with space: ${near.name} (${near.open} open)`;
    console.log('[notify]', msg);
    const existing = document.getElementById('toast');
    if (existing) existing.remove();
    const t = document.createElement('div');
    t.id = 'toast';
    t.textContent = msg;
    Object.assign(t.style, {position:'fixed', right:'16px', bottom:'16px', padding:'10px 14px', background:'#142032', color:'#e8eef7', border:'1px solid #2a364a', borderRadius:'10px'});
    document.body.appendChild(t);
    setTimeout(()=> t.remove(), 4500);
  }
}

locateBtn.onclick = () => {
  navigator.geolocation?.getCurrentPosition(pos => {
    userLatLng = { lat: pos.coords.latitude, lng: pos.coords.longitude };
    L.marker([userLatLng.lat, userLatLng.lng]).addTo(map).bindPopup('You are here').openPopup();
    map.setView([userLatLng.lat, userLatLng.lng], 16);
  }, () => alert('Location unavailable.'));
};

typeFilterEl.onchange = renderSidebar;
minOpenEl.oninput = renderSidebar;
notifyToggle.onchange = () => maybeNotify();

loadLots().then(startSimulation);
