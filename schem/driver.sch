v 20130925 2
C 32400 41500 1 0 0 DRV8825-breakout.sym
{
T 32400 45340 5 10 0 0 0 0 1
device=DRV8825_BREAKOUT
T 32400 44740 5 10 0 0 0 0 1
footprint=DIP16_600.fp
T 33900 44400 5 10 1 1 180 6 1
refdes=U1
}
C 38900 44900 1 0 0 rj45-1.sym
{
T 38900 47800 5 10 0 0 0 0 1
device=RJ45
T 38900 47600 5 10 0 0 0 0 1
footprint=RJ45_NEUTRIK_NE8FBH.fp
T 38900 46800 5 10 1 1 0 0 1
refdes=CONN0
}
C 38600 42600 1 0 0 sn75176-1.sym
{
T 40300 44400 5 10 1 1 0 6 1
refdes=U11
T 38900 44550 5 10 0 0 0 0 1
footprint=DIP8
T 38900 45550 5 10 0 0 0 0 1
device=DS75176
}
C 44800 45900 1 0 0 lm7805-1.sym
{
T 46400 47200 5 10 0 0 0 0 1
device=7805
T 46200 46900 5 10 1 1 0 6 1
refdes=U2
T 44800 45900 5 10 1 1 0 0 1
footprint=TO220SW
}
C 40000 45800 1 0 0 gnd-1.sym
C 47200 46500 1 0 0 vcc-1.sym
N 39800 46300 39800 47500 4
N 39800 46500 44800 46500 4
N 39800 45900 39800 46100 4
N 39800 46100 40100 46100 4
C 45500 45300 1 0 0 gnd-1.sym
N 38600 43000 38600 43600 4
N 38600 43600 38300 43600 4
C 38200 42400 1 0 0 gnd-1.sym
C 42500 43000 1 90 0 capacitor-1.sym
{
T 41800 43200 5 10 0 0 90 0 1
device=CAPACITOR
T 42400 43600 5 10 1 1 0 0 1
refdes=C11
T 41600 43200 5 10 0 0 90 0 1
symversion=0.1
T 42400 43200 5 10 1 1 0 0 1
value=100n
T 42500 43000 5 10 1 1 0 0 1
footprint=ACY200
}
C 38400 42700 1 90 0 resistor-2.sym
{
T 38050 43100 5 10 0 0 90 0 1
device=RESISTOR
T 38100 43300 5 10 1 1 180 0 1
refdes=R11
T 38100 43100 5 10 1 1 180 0 1
value=10k
T 38400 42700 5 10 1 1 0 0 1
footprint=ACY400
}
N 40600 43000 42300 43000 4
N 42300 43900 40600 43900 4
C 42200 42700 1 0 0 gnd-1.sym
C 42100 43900 1 0 0 vcc-1.sym
N 39800 45700 41200 45700 4
N 41200 45700 41200 43300 4
N 41200 43300 40600 43300 4
N 39800 45500 40900 45500 4
N 40900 45500 40900 43600 4
N 40900 43600 40600 43600 4
C 38600 40000 1 0 0 sn75176-1.sym
{
T 38900 41950 5 10 0 0 0 0 1
footprint=DIP8
T 38900 42950 5 10 0 0 0 0 1
device=DS75176
T 40300 41800 5 10 1 1 0 6 1
refdes=U12
}
N 38600 40400 38600 41000 4
N 38600 41000 38300 41000 4
C 38200 39800 1 0 0 gnd-1.sym
C 42500 40400 1 90 0 capacitor-1.sym
{
T 41800 40600 5 10 0 0 90 0 1
device=CAPACITOR
T 41600 40600 5 10 0 0 90 0 1
symversion=0.1
T 42400 41000 5 10 1 1 0 0 1
refdes=C12
T 42400 40600 5 10 1 1 0 0 1
value=100n
T 42500 40400 5 10 1 1 0 0 1
footprint=ACY200
}
C 38400 40100 1 90 0 resistor-2.sym
{
T 38050 40500 5 10 0 0 90 0 1
device=RESISTOR
T 38100 40700 5 10 1 1 180 0 1
refdes=R12
T 38100 40500 5 10 1 1 180 0 1
value=10k
T 38400 40100 5 10 1 1 0 0 1
footprint=ACY400
}
N 40600 40400 42300 40400 4
N 42300 41300 40600 41300 4
C 42200 40100 1 0 0 gnd-1.sym
C 42100 41300 1 0 0 vcc-1.sym
N 40600 40700 41800 40700 4
N 40600 41000 41500 41000 4
N 39800 45300 41800 45300 4
N 41800 45300 41800 40700 4
N 39800 45100 41500 45100 4
N 41500 45100 41500 41000 4
N 34400 43900 38600 43900 4
N 38600 41300 37700 41300 4
T 38200 41300 9 10 1 0 0 0 1
STEP
T 38300 43900 9 10 1 0 0 0 1
DIR
C 44300 46500 1 270 0 capacitor-2.sym
{
T 45000 46300 5 10 0 0 270 0 1
device=POLARIZED_CAPACITOR
T 44400 46300 5 10 1 1 180 0 1
refdes=C2
T 45200 46300 5 10 0 0 270 0 1
symversion=0.1
T 44000 45800 5 10 1 1 0 0 1
value=470u
T 44300 46500 5 10 1 1 0 0 1
footprint=RCY200P
}
C 47600 45600 1 90 0 capacitor-1.sym
{
T 46900 45800 5 10 0 0 90 0 1
device=CAPACITOR
T 47500 46200 5 10 1 1 0 0 1
refdes=C4
T 46700 45800 5 10 0 0 90 0 1
symversion=0.1
T 47500 45800 5 10 1 1 0 0 1
value=100n
T 47600 45600 5 10 1 1 0 0 1
footprint=ACY200
}
C 46500 46500 1 270 0 capacitor-2.sym
{
T 47200 46300 5 10 0 0 270 0 1
device=POLARIZED_CAPACITOR
T 46600 46300 5 10 1 1 180 0 1
refdes=C3
T 47400 46300 5 10 0 0 270 0 1
symversion=0.1
T 46200 45800 5 10 1 1 0 0 1
value=100u
T 46500 46500 5 10 1 1 0 0 1
footprint=RCY200P
}
N 46400 46500 47400 46500 4
N 44500 45600 47400 45600 4
N 45600 45900 45600 45600 4
N 37700 41300 37700 43600 4
N 37700 43600 34400 43600 4
C 35600 42500 1 180 0 resistor-2.sym
{
T 35200 42150 5 10 0 0 180 0 1
device=RESISTOR
T 35100 42700 5 10 1 1 180 0 1
refdes=R1
T 35500 42700 5 10 1 1 180 0 1
value=10k
T 35600 42500 5 10 1 1 0 0 1
footprint=ACY400
}
N 34400 42100 34400 42400 4
C 35700 42400 1 0 0 vcc-1.sym
N 35900 42400 35600 42400 4
C 30100 41700 1 0 0 input-2.sym
{
T 30100 41900 5 10 0 0 0 0 1
net=POWER24V:1
T 30700 42400 5 10 0 0 0 0 1
device=none
T 30600 41800 5 10 1 1 0 7 1
value=24V
}
C 39800 47600 1 180 0 output-2.sym
{
T 38900 47400 5 10 0 0 180 0 1
net=POWER24V:1
T 39600 46900 5 10 0 0 180 0 1
device=none
T 38900 47500 5 10 1 1 180 1 1
value=24V
}
C 32300 40600 1 0 0 gnd-1.sym
C 32000 43600 1 0 0 gnd-1.sym
N 32400 43900 32100 43900 4
C 34500 44200 1 0 0 vcc-1.sym
N 34400 43000 34700 43000 4
N 34700 43000 34700 44200 4
N 34400 43300 34700 43300 4
C 32200 41800 1 270 0 capacitor-2.sym
{
T 32900 41600 5 10 0 0 270 0 1
device=POLARIZED_CAPACITOR
T 32300 41600 5 10 1 1 180 0 1
refdes=C1
T 33100 41600 5 10 0 0 270 0 1
symversion=0.1
T 31900 41100 5 10 1 1 0 0 1
value=100u
T 32200 41800 5 10 1 1 0 0 1
footprint=RCY200P
}
N 31800 42100 32400 42100 4
N 32400 40900 31800 40900 4
N 31800 40900 31800 42100 4
N 31500 41800 32400 41800 4
N 34700 42400 34400 42400 4
C 30400 42200 1 0 0 connector4-1.sym
{
T 32200 43100 5 10 0 0 0 0 1
device=CONNECTOR_4
T 30400 43600 5 10 1 1 0 0 1
refdes=CONN_STEPPER
T 30400 42200 5 10 1 1 0 0 1
footprint=SIP4
}
N 32100 42700 32400 42700 4
N 32100 43000 32400 43000 4
N 32100 42400 32400 42400 4
N 32100 43300 32400 43300 4
