function initnav() {
document.getElementById("navMenu").innerHTML = 
  '<div class="navbar">' +
  '<a href="index.html">Home</a>' +
  '<div class="dropdown">' +
    '<a href="index.html">Metrics</a>' +
    '<div class="dropdown-content">' +
      '<a href="index.html">M1: Whois</a>' +
      '<a href="graph-m2.html">M2: Abuses</a>' +
      '<a href="graph-m3.html">M3: Root Servers</a>' +
      '<a href="graph-m4.html">M4: Usage</a>' +
      '<a href="index.html">M5: Accuracy</a>' +
      '<a href="graph-m6.html">M6: IANA</a>' +
      '<a href="graph-m7.html">M7: DNSSEC</a>' +
    '</div>' +
  '</div>' +
  '<a href="index.html">Participate</a>' +
  '<a href="index.html">About</a>' +
 '</div>'
}