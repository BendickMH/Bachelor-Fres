# Bachelor-Fres - Logg


## 31.03.2022 Midtveis Presentasjon tilbakemelding

Tilbakemeldinger på presentasjonen: 
- Passe på dato og bunntekst.
- Tydelig Kilder på bildene vi har hentet fra nettet.
- Kanskje en video eller gif? 


## 07.04.2022 Samtale med frikk

Frikk nevnte av vi burde lage en github for å ha oversikt over programmeringen.
Han snakket også om at vi burde se over klokkehastighetene til raspberry pi og arduino og sjekke om hvilken som er best egnet til styring av motorene. Frikk mente arduinoen var best egnet, men vi burde undersøke selv.

Arduinoen sin klokkehastighet ligger på 16Mhz mens raspberry ligger på  1.8 Ghz.
Fordelen med Arduino er at det er lett å koble, programmere og kommunisere seriellt. ulempen er da lagringsplass og programmerings forståelse.

Raspberry pi er en kompakt mikro pc som vi kan programmere direkte inn i, men har en bratt læringskurve og kan være problematisk for oss som aldri har brukt linux, eller programmert i andre språk enn C# (dog det er mulig å programmere C# i RPI, så virker det for oss som at det ikke er like rett fram som med feks windows pc og VSCode, dette kan vi ta feil med)

Et annet punkt å vurdere er lagrings kapasitet. Å programmere arduino til å kjøre G-Kode krever mye optimalisering for å bruke minst mulig minne. Etter testing bruker grbl ca. 92% av minnet til arduino, dette med mye optimalisering.

Frikk tipset oss også om hvordan vi kunne bruke RaspberryPI som en webserver av et slag, som et mellomledd mellom PC og Arduino, slik at den sender kommandoer og kommuniserer med arduino.

## 11.04.2022 Programmerings planlegging og kobling av maskin

Vi lagde et dokument for planlegging av program. Det er et word dokument som har lister med planlagte program deler og nødvendig innhold. Dokumentet er et "levende" dokument som oppdateres flittig.

Vi har også begynt å lodde krets kort og gjør klart for oppkobling av CNC maskinen

## 13.04.2022 Tar lærdom fra grbl

Har brukt majoriteten av dagen på å sette opp arduino programmet slik at det bruker minst mulig minne. Dette er gjort ved å se på grbl sin kilde-kode og prøvd å forstå hva
de har gjort og hvorfor. Det er en utfordring ettersom at arduino programmeres i C++, noe vi ikke har gått igjennom som kurs på skolen, men det er overkommelig med mye googling.

Det har blitt lagt inn forskjellige filer på src mappen, mange (om ikke de fleste) filene inneholder mye kode fra grbl foreløpig men forhåpentligvis ikke for alltid. Dette er slik at vi kan se sammenhengen og forstå hvordan deres oppsett fungerer med arduino.

Jeg har så langt lagt merke til to tydelige hindere i oppgaven så langt:
1. Vi bruker TMC 5160 BOB Stepper drivere, som har eget bibliotek til arduino som tar mye minne om brukt, men jeg har ikke funnet en annen måte å styre dem på enn igjennom biblioteket. Dette hadde nok ikke vært et problem for en dreven C++ utvikler.
2. grbl er ganske avansert i forhold til hva vi klarer å forstå, og kan dermed være litt utenfor våres programmerings forståelse. Det hjelper heller ikke at grbl skrives i C++ som gir en ekstra utfordring i forhold til hva og hvordan.

Dette er nok overkommelige hindringer, men krever mye tid på lesing som tar tid vekk fra selve programmeringen og produkt utviklingen.

Ellers har opplæringen av EEPROM begynt, det var et relativt ukjent konsept som nå virker essensielt for å få et fungerende bra prosjekt. Arduino UNO, som er brettet vi bruker, har 1KB med tilgjengelig EEPROM. Vi kommer til å prøve å bruke dette til å lagre instillinger for vår maskin, så det ikke trengs å skrives inn ved hver oppstart.

## 14.04.2022 Problemer med drivere

Vi bruker TMC 5160-BOB v1.4 som våre stepper drivere. Disse fungerer fint når man lager et rett fram program for å drive stepper motorene. Tidligere fikk vi de til å snurre fint, med diverse hastigheter, akselerasjons rater og microsteps, dette grunnet et fint bibliotek kalt TMCStepper.h som kan lastes ned fra github eller igjennom Platform.io.

Problemet kommer når man skal kombinere den med andre bibliotek eller selvlagde, som vi holder på med. Vi får mange definisjons og deklarerings konflikter.

En løsning kan være å skumme igjennom TMCStepper biblioteket, og forstå hvordan de driver motorene via SPI. evt bruke step/dir på driver for å unngå bruk av bibliotek.

## 15.04.2022 Langfredag beskriver ikke dagen godt nok

Brukt dagen på å sile igjennom grbl sin kilde kode etter inspirasjon og forståelse for å drive en CNC fres. 

Det har gått litt opp for meg at SPI kanskje ikke er beste måten å gå fram på.
Fordelen vi så med SPI er at vi får tilbakemelding fra driver om hvilken posisjon stepper motoren har. Derimot ser jeg fler ulemper: Det krever flere pins, det krever spesifikke pins, det krever eksternt bibliotek(som kanskje ikke er kompitabel) og tilbakemeldingen burde ikke ha så mye å si, ettersom det kanskje er like greit å holde styr på posisjoneringen selv.

Ellers har langfredagen levd opp til navnet sitt, og har gitt meg god tid til å selvlære C++ via grbl. Dette er en tung og vanskelig prossess men hjelper godt med forståelsen på hvordan mikrokontrollere som arduino fungerer og opererer.

Prosjektet ser overkommelig ut, men vi må nok få flere lange dager før innleveringsfristen kommer.

## 19.04.2022 Kobling av maskinen

Vi har montert ledning lokkene til motorene, festet koblingspunktene og koblet opp kablene til motorene og limit switchene. Det har vært litt problematisk å feste motorlokkene etterson skuehullene ikke var store nok, samt vi hadde ikke riktige skruer, men det så mye bedre ut med dem på uansett. Vi måtte også bore hull for feste av ledningene til motorlokkene så stresspunktet ikke lå på koblingspunktet.

Vi har også loddet mye av kretskortet og begynner å få koblet sammen alt slik at det skal fungere med SPI. På den fronten har vi bestemt oss for å kjøpe en arduino mega slik at vi får mer lagringsplass på arduinoen, på den måten slipper vi å bekymre oss for mye over å programmere super optimalt, og kan heller ha større fokus på funksjonalitet. Vi får med det også større mulighet til å bruke SPI og limitswitcher siden flere pinner blir da tilgjengelig for oss.

## Bilder

<img src="https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/IMG_1011.jpg" width=50% height=50%>

Oppkobling av to motordrivere til arduino TMC 5160 bob V1.4 drivere er brukt

<img src="https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/IMG_1030.jpg" width=50% height=50%>

Ferdig bygd Z-Akse

<img src="https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/IMG_1033.jpg" width=50% height=50%>
<img src="https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/IMG_1035.jpg" width=50% height=50%>

Ferdig montert ramme og "gantry", motorene er montert. 

