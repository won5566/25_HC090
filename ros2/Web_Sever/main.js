let map = L.map('map').setView([37.5665, 126.9780], 16); // Default: Seoul
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
  maxZoom: 19,
  attribution: '&copy; OpenStreetMap contributors'
}).addTo(map);

let marker = L.marker([37.5665, 126.9780]).addTo(map);
let statusEl = document.getElementById('status');

async function updatePosition() {
  try {
    const res = await fetch('/position', {cache: 'no-store'});
    const data = await res.json();
    if (data.lat && data.lon) {
      marker.setLatLng([data.lat, data.lon]);
      map.setView([data.lat, data.lon], map.getZoom());
      statusEl.innerText = `Lat: ${data.lat.toFixed(7)}, Lon: ${data.lon.toFixed(7)} @ ${data.timestamp || ''}`;
    } else {
      statusEl.innerText = 'Waiting for GNSS data…';
    }
  } catch (e) {
    statusEl.innerText = 'Error fetching /position';
  }
}

setInterval(updatePosition, 1000);
updatePosition();


