# Vzdálenost letadel

Úkolem je vytvořit program, který pomůže obsluze radaru řídící věže.

Při řízení letového provozu je důležité hlídat potenciální kolize letadel. Radary snímají pozice letadel a program kontroluje vzdálenosti mezi letadly. Chceme realizovat program, který pro zadané souřadnice letadel rozhodne, kde hrozí potenciální kolize, tedy která letadla jsou k sobě nejblíže.

Vstupem program jsou souřadnice a označení letadel. Pro jednoduchost předpokládáme, že souřadnice letadel jsou rovinné, tedy pozice letadla je určena x a y souřadnicí. Souřadnice mají podobu desetinných čísel. Souřadnice jsou oddělené čárkou, po zadání souřadnic následuje dvojtečka a název (identifikace) letadla. Název letadla je řetězec bez mezer a bílých znaků, nejvýše 199 znaků dlouhý, a není jednoznačný (na vstupu mohou existovat dvě nebo i více letadel se stejným názvem). Takto zadaných letadel může být na vstupu velmi mnoho, jejich počet není dopředu známý. Zadávání končí s aktivním koncem souboru (EOF na stdin). Formát vstupu je zřejmý z ukázek níže.

Výstupem program je vzdálenost dvojice nejbližších letadel. Pokud je v té samé (nejmenší) vzdálenosti více dvojic letadel, program vypíše počet dvojic letadel v této (nejmenší) vzdálenosti. Následuje výpis všech dvojic letadel, která mají mezi sebou tuto (nejmenší) vzdálenost. Výpis dvojic letadel nemá určené pořadí (řádky výpisu mohou být libovolně uspořádané, stejně tak i letadla ve dvojici na řádce). Při porovnání si testovací prostředí výpis případně upraví.

Program musí ošetřovat vstupní data. Pokud jsou vstupní data nesprávná, program to zjistí, zobrazí chybové hlášení a ukončí se. Za chybu je považováno:

 - nečíselné souřadnice (není platné desetinné číslo),
 - chybějící/přebývající oddělovače (čárka, dvojtečka),
 - méně než dvě letadla na vstupu (jinak není definovaná nejmenší vzdálenost).

Váš program bude spouštěn v omezeném testovacím prostředí. Je omezen dobou běhu (limit je vidět v logu referenčního řešení) a dále je omezena i velikost dostupné paměti. V závislosti na zvoleném algoritmu může být úloha výpočetně náročnější. Správná implementace naivního algoritmu projde všemi testy kromě testu bonusového, tedy má šanci získat nominálních 100% bodů. Pro zvládnutí bonusového testu je potřeba použít efektivnější algoritmus, který dokáže v krátkém čase zvládnout větší objem testovacích dat (velké množství letadel).

## Ukázka práce programu:
Pozice letadel:\
0,0: KLM\
5,0: Lufthansa\
10,0: SmartWings\
7,0: AirFrance\
2,0: Qantas\
Vzdalenost nejblizsich letadel: 2.000000\
Nalezenych dvojic: 2\
KLM - Qantas\
Lufthansa - AirFrance\
