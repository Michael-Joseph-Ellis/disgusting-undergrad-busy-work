# TigerPark: Campus Parking Assistant

## Overview
TigerPark is a lightweight prototype web app that helps university students, faculty, and visitors quickly locate available parking spaces on campus. The app provides a real-time style interface with a campus map, lot availability indicators, filters by lot type, and quick directions.  

This project was developed as part of the **Requirements Elicitation Extra Credit Assignment**. The artifact demonstrates how requirements gathered from students (e.g., frustrations with circling for spaces, uncertainty about lot eligibility, and lateness due to parking stress) can be addressed with a practical, high-fidelity prototype.

---

## Features
- **Interactive campus map** powered by Leaflet  
- **Color-coded availability** (green = plenty, yellow = limited, red = nearly full)  
- **Lot filters** by type (student, faculty, visitor) and minimum open spaces  
- **Sidebar lot list** sorted by availability with quick “Pan” and “Directions” buttons  
- **Geolocation support** to center the map on the user’s current location  
- **Simulated real-time updates** to lot data every few seconds  

---

## Tech Stack
- **HTML/CSS/JavaScript** — no build tools required  
- **Leaflet.js** for interactive maps  
- **OpenStreetMap tiles** for base map data  
- **Mock JSON dataset** for parking lots  

---

## How to Run
1. Clone or download this repository.  
2. Open `index.html` in any modern web browser.  
3. Explore the map, filters, and sidebar features.  

_No server setup or installation required. The demo runs entirely client-side._

---

## File Structure
```
campus-parking/
├── index.html # Main UI
├── style.css # Styles and theme
├── app.js # Core logic and interactivity
└── data/lots.json # Mock dataset of parking lots
```

---

## Requirements Traceability
Based on partner interviews, the following requirements guided the prototype:
- **Quick overview of availability:** Implemented via color-coded map markers and open/total counts  
- **Role-based filtering:** Users can filter lots by student/faculty/visitor  
- **Proximity awareness:** Optional geolocation and notifications simulate alerts when nearby lots have spaces  
- **Ease of navigation:** Direct Google Maps links provide instant walking/driving directions  

---

## Limitations & Future Work
- Uses mock data with simulated changes — not connected to real sensors or campus APIs  
- No authentication or enforcement of parking eligibility  
- Notifications are simplified in-page alerts rather than full push notifications  

**Future improvements could include:**
- Integrating live data feeds from campus IoT sensors  
- Adding accessibility filters (e.g., ADA spots, van access)  
- Predictive availability during peak hours or events  
- Integration with university single sign-on (SSO) for role-based restrictions  

---

## License
This project is for educational purposes only and not affiliated with Clemson University (or any campus authority). Do not use it for actual parking guidance.
