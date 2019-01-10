xv6-käyttöjärjestelmä

Kuinka ajetaan?

§sudo apt install git
§sudo apt install qemu
§git clone https://github.com/Timpp4/kaytsys.git
§cd proj3/xv6-public/
§make
§make qemu

Tätä projektia varten on luotu uusi ohjelma (grc), jota kutsuessa tulostuu read() system callin käyttökerrat.
Seuraavia tiedostoja on muokattu, jotta getreadcount() saadaan toimimaan.

syscall.h
defs.h
user.h
sysproc.c
usys.S
syscall.c
proc.c
grc.c
Makefile
sysfile.c
tieto.h

Pääsääntöisesti koodia on tullut vain määrittelyiden verran lisään ko. eri tiedostoihin. proc.c
-tiedostoon on kirjoitettu koodia, jotta toiminnallisuus saataisiin vaaditulle tasolle.
Käytännössä on tehty uusi system call, jota voi kutsua grc:llä. GetReadCount on käyttäjälle
näkyvä ja käyttäjä voi itse kutsua sitä
