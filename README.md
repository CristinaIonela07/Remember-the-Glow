Descrierea jocului:
 1. Pe matricea principala de LED-uri se va aprinde un LED.
 2. Pe cele doua matrici secundare de LED-uri se vor forma doua imagini. Matricile sunt conectate serial, miscorand astfel numarul de pini digitali necesari de pe microcontroler.
 3. Prin intermediul a doua butoane, simbolizand DA sau NU, jucatorul trebuie sa raspunda corect la intrebarea: “Cele doua imagini sunt la fel?”
 4. Se repeta pasii anteriori de 6 ori.
 5. Prin intermediul unei matrice de butoane, corespunzatoare LED-urilor de pe matricea principala, jucatorul trebuie sa introduca corect secventa de LED-uri aprinse anterior.
 6. Daca utilizatorul introduce corect secventa de lumini SI a raspuns corect la toate intrebarile referitoare la imagini, inseamna ca a castigat si se vor inalta steagurile victoriei, pe fundalul unei melodii triumfatoare.
Atentie la timp! Nu ai o vesnicie sa te gandesti.

Piese utilizate:
 - Arduino MEGA2560
 - Matrice de LED-uri MAX7219 - folosite pentru reprezentarea efectiva a jocului: o matrice va reda secventa de lumini ce trebuie memorata, iar celelalte doua vor fi folosite pentru a arata jucatorului diferite combinatii de lumini (imagini)
 - Matrice de butoane 4×4 - permite jucatorului sa introduca secventa de lumini
 - Micro Servomotor SG90 - atunci cand jucatorul a castigat servomotoarele vor flutura mici stegulete
 - 4-Digit Display - folosit ca si cronometru, pentru a aminti jucatorului cat timp mai are
 - Butoane extra - doua la numar, folosite pentru ca jucatorul sa spuna daca cele doua matrici de LED-uri arata aceeasi imagine
 - Buzzer - folosit pentru a reda diferite sunete si melodii, in functie de momentul jocului

In dezvoltarea si testarea proiectului am folosit mediul de dezvoltare Arduino IDE.
Exista multiple fisiere .h care contin variabile specifice fiecarei componente, declarate si initializate.
Toate functiile au fost implementate in proiect_pm.ino.

Pentru simplitatea controlului pieselor am utilizat urmatoarele biblioteci:
- LedControl pentru Matricile de LED-uri MAX7219
- Adafruit_Keypad pentru Matricea de butoane
- TM1637Display pentru Cronometru (Temporizator)
- ezBuzzer pentru Buzzer
