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

## 20.04.2022 Kobling av maskin part 2

Loddet ferdig koblings/krets kortet:
Mens Kim og Bendick var i elektriske maskiner timer loddet erik sammen kretskortet med driverene.

Koblet sammen maskinen, krets kortet, strømforsyning og arduino:
Vi koblet sammen kretskortet til motorene og strømforsyning og laget ett kjapt test program på arduino. Vi fikk litt problemer med at noen av komblingene til motorene var feil, og måtte da se over de. Til slutt fikk vi bevegelse i Y aksen.

Testet X,Y og Z:

Vi testet deretter X og Z og så at Z beveget seg fint mens X hadde problemer, og har sannsynligvis da blitt feilkoblet.
Vi testet arduino mega og dens egenskaper og lagringsplass.

## 21.04.2022

Test forslag av Endre, probe testing med metall plate for å teste repetisjon og nøyaktighet

Ferdig lodding og testing av aksene

Plate på maskin, Lars, treverksted, niter osv

planlegging av styreboksen

testing av arduino mega og programmering av enkel akse test og hastighet

## 22.04.2022

Programmering av CPU_MAP

Anskaffelse av niter og festing av de

Testing av koblinger

## 05.05.22     

Fikk bevegelse i alle aksene med de nye driverne DRV8825, men ikke helt problemfritt. Vi oppdaget høyfrekvente lyder og "stallgriding". Skrapende lyder som indikerer for lite dreiemoment. Vi gikk over fra en PSU til to som kan levere opp til 30V, hvor vi har to motorer på hver. Fått kjeft igjen av Endre for treboksen, så bør skaffe oss en i plast eller metall. Vi hadde et møte med Frikk der vi fikk to DRV8825 og nyttige tips om fortsettelsen på oppgaven, som: Demo mode, høyere logikk system.

Dyrere drivere har såpass høy frekvens at vi ikke ville hørt de, men DRV8825 kjører på lavere frekvens som kan høres av mennesker. Billige drivere bråker mer, mindre spenningståleranse og krever mer kjøling. Disse er valgt med tanke på budsjett. Bør ta enda flere bilder og videoer!!

## 11.05.22 og 12.05.22 

Fått fikset plastboksen så endre blir fornøyd!! Koblet opp alt permanent, og tester de forskjellige aksene. Z-Aksen er bra, Y-Aksen er helt forferdelig. Den Hakker hele tiden og klarer ikke gjøre bevegelsen i en hel fin bevegelse (Se Video). X-Aksen virker som de går litt forskjellig tempo. Her har vi endret oppsette fra tidliger og kjører nå ett driverkort til hver steppermotor og ikke at motorene på X-aksen deler driverkort. Denne hakker også mer enn tidligere. Vi har prøvd med enda en PSU, men ikke noe endret seg. Byttet Z og Y aksen for å se om det er driverkortet eller koblingen på koblingsbrettet til driverkortet. Dette må feilsøkes på i morgen!!!

## 13.05.22

Starter dagen med å bytte om på koblingen til Z og Y aksen og fant ut at problemet ligger på Y aksen sin kobling. Sendte mail til Frikk for å få tips på hva dette jævelskapet kan være. DET ER JO SELVFØLGELIG CURRENT LIMITEN!! Vi har tatt utgangspunkt i Z-aksen som referansepunkt ettersom den går veldig bra. Vi endte på 1,05V-1.15V og har stilt alle inn på det. Nå går den finere enn noen gang og tegner endelig hele logoen vi har teste med uten å tegne ting oppå hverandre. 
Nå skal vi få limitswitchene opp å gå det blir vel noe jævelskap med de også. Kommer snart tilbake med resultate. Ikke vent i spenning!

### Fortsettelse 13.05.22

Fikk også limitswitchene opp å gå etter litt trøbbel her også. Brukte en ekstern 5V spenningskilde, men det funket ikke. Arduinoen klarte ikke å detektere spenningsfallet på switchene, så vi droppet spenningskilden og hentet spenning rett fra arduinoen og de funket. Etter dette gikk resten av dagen på å teste litt forskjellige motiver. De som er på bilde under og noen litt mer avanserte som kommer bilde og video av lenger nede. Som vist på test 5 at Y aksen måtte kalibreres ettersom at den tegnet utenfor arket. Dette ble rettet opp og test nr.6 syntes vi ser veldig bra ut! 



## Bilder

<img src="https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/IMG_1011.jpg" width=50% height=50%>

Oppkobling av to motordrivere til arduino TMC 5160 bob V1.4 drivere er brukt

<img src="https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/IMG_1030.jpg" width=50% height=50%>

Ferdig bygd Z-Akse

<img src="https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/IMG_1033.jpg" width=50% height=50%>
<img src="https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/IMG_1035.jpg" width=50% height=50%>

Ferdig montert ramme og "gantry", motorene er montert. 
Test 1-4 Logo.
<img src= "https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/279728807_954451605243568_1355811422471876527_n.jpg" width=50% height=50%>
<img src= "https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/279296945_1425440631291535_5160818057353762292_n.jpg" width=50% height=50%>
<img src= "https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/279242542_666167861086248_2556704246501396964_n.jpg" width=50% height=50%>
<img src= "https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/279218236_686944822364502_1902900006388356436_n.jpg" width=50% height=50%>

Test 5-  Navn, firkant, sirkel og test nr.
<img src= "https://github.com/BendickMH/Bachelor-Fres/blob/main/Bilder/280502743_741153460351839_3622160828386684238_n.jpg" width=50% height=50%>


Forskjellige tester
 

