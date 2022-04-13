# Bachelor-Fres


## Programmerings mål:

### C#:

**Generelt:**
- [ ] Seriell kommunikasjon

**G-Kode Tolk:**
- [ ] Motor kontroll
- [ ] Posisjon/Step Beregninger
- [ ] Akselerasjons Beregninger
- [ ] Visualisering av koden?

**GUI:**
- [ ] Jog (0.1,1,10)mm
- [ ] Hjem knapp (0,0,0)xyz
- [ ] Fil opplastning
- [ ] Sett arbeidspunkt (start av materiale)

### Arduino:

**Generelt:**
- [ ] Seriell kommunikasjon

**Motor:**
- [ ] Motta argumenter/Kommando fra C#
- [ ] Tilbakemelding om posisjon
- [ ] Godkjenning til mottak av neste kommando
- [ ] Hardkode Z-Limits


**Knapper/Interrupts:**
- [ ] Limit switch
- [ ] Nødstopp


## Loggføring av prosjekt:

### 31.03.2022 Midtveis Presentasjon tilbakemelding

Tilbakemeldinger på presentasjonen: 
- Passe på dato og bunntekst.
- Tydelig Kilder på bildene vi har hentet fra nettet.
- Kanskje en video eller gif? 


### 07.04.2022 Samtale med frikk

Frikk nevnte av vi burde lage en github for å ha oversikt over programmeringen.
Han snakket også om at vi burde se over klokkehastighetene til raspberry pi og arduino og sjekke om hvilken som er best egnet til styring av motorene. Frikk mente arduinoen var best egnet, men vi burde undersøke selv.

Frikk tipset oss også om hvordan vi kunne bruke RPI som en webserver av et slag, som et mellomledd mellom PC og Arduino, slik at den sender kommandoer og kommuniserer med arduino.

### 11.04.2022 Programmerings planlegging og kobling av maskin

Vi lagde et dokument for planlegging av program. Det er et word dokument som har lister med planlagte program deler og nødvendig innhold. Dokumentet er et "levende" dokument som oppdateres flittig.

Vi har også begynt å lodde krets kort og gjør klart for oppkobling av CNC maskinen

### 13.04.2022 Tar lærdom fra grbl

Har brukt majoriteten av dagen på å sette opp arduino programmet slik at det bruker minst mulig minne. Dette er gjort ved å se på grbl sin kilde-kode og prøvd å forstå hva
de har gjort og hvorfor. Det er en utfordring ettersom at arduino programmeres i C++, noe vi ikke har gått igjennom som kurs på skolen, men det er overkommelig med mye googling.

Det har blitt lagt inn forskjellige filer på src mappen, mange (om ikke de fleste) filene inneholder mye kode fra grbl foreløpig men forhåpentligvis ikke for alltid. Dette er slik at vi kan se sammenhengen og forstå hvordan deres oppsett fungerer med arduino.

Jeg har så langt lagt merke til to tydelige hindere i oppgaven så langt:
1. Vi bruker TMC 5160 BOB Stepper drivere, som har eget bibliotek til arduino som tar mye minne om brukt, men jeg har ikke funnet en annen måte å styre dem på enn igjennom biblioteket. Dette hadde nok ikke vært et problem for en dreven C++ utvikler.
2. grbl er ganske avansert i forhold til hva vi klarer å forstå, og kan dermed være litt utenfor våres programmerings forståelse. Det hjelper heller ikke at grbl skrives i C++ som gir en ekstra utfordring i forhold til hva og hvordan.

Dette er nok overkommelige hindringer, men krever mye tid på lesing som tar tid vekk fra selve programmeringen og produkt utviklingen.

## Bilder

<img src="https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/IMG_1011.jpg" width=50% height=50%>

Oppkobling av to motordrivere til arduino TMC 5160 bob V1.4 drivere er brukt

<img src="https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/IMG_1030.jpg" width=50% height=50%>

Ferdig bygd Z-Akse

<img src="https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/IMG_1033.jpg" width=50% height=50%>
<img src="https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/IMG_1035.jpg" width=50% height=50%>

Ferdig montert ramme og "gantry", motorene er montert. 

