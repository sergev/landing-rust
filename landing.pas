(*=p-,t-,l-*)_program LANDING;

_procedure landing(eng: boolean);
_label 1, 4410, 4514, 4636;
_type arr = _array [1..21] _of real;
_var frame: @arr; saved: arr; cost, Vfps, elapsed, altitude, Vmps, mass: real;
drymass, lunarG, impulse, remaining, value, newalt, newVmps, x, x2, x3, x4, x5, deltaT: real;
interval, cursec, ruined, fuel, msgarg:integer; verbose: boolean;

_procedure landMsg(msg: integer); _(
_if eng _then _case msg _of
0: write('I UNDЕRSТООD IТ AS NIL.');
1: write('МISSIОN CОNТRОL ОUТ.');
2: write('УОU BLЕW IТ AGAIN. WЕLL, ТНIRD ТIМЕS ТНЕ CНARМ.....');
3: write('НОW DОЕS IТ FЕЕL ТО ТASТЕ DЕAТН ТRЕЕ ТIМЕS....??');
4: write('NЕХТ ТIМЕ BRING ALОNG УОUR BIBLЕ.');
5: write('DО NОТ AРРLУ ТО NASA FОR A JОB. УОU''LL NЕVЕR МAКЕ IТ.');
6: write('УОU''VЕ RUINЕD SIХ МISSIОNS NОW. ТURN IN УОUR SРACЕSUIТ.');
7: write('.......SРLAТ.  NОТ SО GООD.  INЕХРЕRIЕNCЕ РЕRНAРS.');
8: _( write('МISSIОN CОNТRОL CALLING LUNAR МОDULЕ:
МANUAL CОNТRОL IS NЕCЕSSARУ FОR LANDING.
WНAТ IS УОUR ЕХРЕRIЕNCЕ:
 0 1 2(SТANDARD) 3 4 5 6 7 8 9(NО ЕХРЕRIЕNCЕ) ?') _);
9: write('УОU МUSТ SРЕCIFУ A FUЕL RAТЕ ЕACН 10 SЕCОNDS.
RAТЕS МUSТ BЕ ZЕRО ОR BЕТWЕЕN 8 AND 200 LBS.РЕR SЕC.');
10: write('УОU НAVЕ ', msgarg:0, ' LBS ОF FUЕL.
CAРSULЕ WЕIGНТ IS NОW 32500 LBS INCLUDING FUЕL.
CОММЕNCЕ LANDING РRОCЕD.');
11: write('FIRSТ RADAR CНЕCК CОМING UР:
 ТIМЕ(SЕC) ALТ(МILЕS + FЕЕТ) VЕLОCIТУ(FРS) FUЕL(LBS)');
12: write('DОN''Т WASТЕ ТIМЕ ТRУING ТО BURN AТ ТНAТ RAТЕ.');
13: write('FUЕL ОUТ AТ ', msgarg:0, ' SЕCОNDS.');
14: write('ОN ТНЕ МООN AТ ', msgarg:0,  ' SЕCОNDS.');
15: write('IМРACТ VЕLОCIТУ ОF ', msgarg:0, ' F.Р.S.');
16: write('FUЕL LЕFТ ', msgarg:0, ' LBS.');
17: write('РЕRFЕCТ LANDING. УОU LUCКУ JЕТ JОCКЕУ.');
18: write('A GООD LANDING, NОТ GRЕAТ, JUSТ GООD.');
19: write('BUCК RОGЕRS УОUR NОТ, BUТ CОNGRAТULAТIОNS, УОU''RЕ DОWN.');
20: write('НЕAVУ CRAFТ DAМAGЕ, УОU МAУ NЕVЕR SЕЕ ЕARТН AGAIN.');
21: write('ТНЕRЕ''S NОW A NЕW LUNAR CRAТЕR ', msgarg:0, ' FЕЕТ DЕЕР.');
22: write('РЕRFЕCТ RЕCОRD. NО FAIR USING CALCULAТING AIDS.');
23: write('NASA WILL DЕDUCТ  ', msgarg:0, ' $ FRОМ УОUR РAУCНЕCК ЕACН WЕЕК');
24: write('FОR ТНЕ L.Е.М. УОU WIРЕD ОUТ.');
25: write('FОR ТНЕ ', msgarg:0, ' L.Е.М.''S УОU WIРЕD ОUТ.')
_end _else _case msg _of
0: write('НЕПОНЯТНО - ПОВТОРИТЕ');
1: write('ПОЛЕТЫ ОКОНЧЕНЫ.');
2: write('ОПЯТЬ НЕУДАЧА. ЧТО Ж - ПОПРОБУЙТЕ В ТРЕТИЙ РАЗ.....');
3: write('КАК ВЫ СЕБЯ ЧУВСТВУЕТЕ, ВСТРЕТИВ СМЕРТЬ ТРИ РАЗА....??');
4: write('В СЛЕДУЮЩИЙ РАЗ ВОЗЬМИТЕ С СОБОЙ БИБЛИЮ.');
5: write('НЕ ПЫТАЙТЕСЬ ПОСТУПИТЬ В NАSА НА РАБОТУ. ВАС НЕ ВОЗЬМУТ.');
6: write('ВЫ ПОГУБИЛИ УЖЕ ШЕСТЬ ПОЛЕТОВ. НАДЕВАЙТЕ СКАФАНДР.');
7: write('.......ШМЯК.  НЕ ОЧЕНЬ ХОРОШО. НАВЕРНОЕ МАЛО ОПЫТА.');
8: write('ЦЕНТР УПРАВЛЕНИЯ ВЫЗЫВАЕТ ЛУННЫЙ МОДУЛЬ:
ДЛЯ ПОСАДКИ ПЕРЕЙДИТЕ НА РУЧНОЕ УПРАВЛЕНИЕ.
КАКОВ ВАШ ОПЫТ: 0 1 2(НОРМА) 3 4 5 6 7 8 9(ОПЫТА НЕТ) ?');
9: write('ВЫ ДОЛЖНЫ УКАЗЫВАТЬ СКОРОСТЬ РАСХОДА ТОПЛИВА ЧЕРЕЗ КАЖДЫЕ 10 СЕКУНД.
РАСХОД ДОЛЖЕН БЫТЬ ИЛИ 0 ИЛИ ОТ 8 ДО 200 ФУНТОВ В СЕКУНДУ.');
10: write('У ВАС ', msgarg:0, ' ФУНТОВ ТОПЛИВА.
ВЕС КАПСУЛЫ СЕЙЧАС 32500 ФУНТОВ, ВКЛЮЧАЯ ТОПЛИВО.
НАЧИНАЙТЕ ПОСАДКУ.');
11: write('ПЕРВЫЙ РАДИОЛОКАЦИОННЫЙ ЗАМЕР ВЫСОТЫ:
ВРЕМЯ(СЕК) ВЫС(МИЛИ  + ФУТЫ) СКОРОСТЬ(Ф/С) ТОПЛ(ФУН)');
12: write('НЕ ТРАТЬТЕ ВРЕМЯ, ПЫТАЯСЬ ЖЕЧЬ ТОПЛИВО С ТАКОЙ СКОРОСТЬЮ.');
13: write('ТОПЛИВО КОНЧИЛОСЬ НА ', msgarg:0,  ' СЕКУНДЕ.');
14: write('НА ЛУНЕ НА ', msgarg:0, ' СЕКУНДЕ.');
15: write('СКОРОСТЬ В МОМЕНТ КАСАНИЯ ', msgarg:0, ' ФУТ/СЕК.');
16: write('ОСТАЛОСЬ ТОПЛИВА ', msgarg:0, ' ФУНТОВ.');
17: write('ИДЕАЛЬНАЯ ПОСАДКА. ВЫ СЧАСТЛИВЫЙ РАКЕТНЫЙ ЖОКЕЙ.');
18: write('ХОРОШАЯ ПОСАДКА, НЕ БЛЕСТЯЩАЯ, ПРОСТО ХОРОШАЯ.');
19: write('ВЫ НЕ БАК РОДЖЕРС, НО ПРИМИТЕ ПОЗДРАВЛЕНИЯ. ВЫ СЕЛИ.');
20: write('КРУШЕНИЕ КОРАБЛЯ. НАВЕРНОЕ ВЫ НИКОГДА НЕ УВИДИТЕ ЗЕМЛЮ.');
21: write('НА ЛУНЕ ВОЗНИК НОВЫЙ КРАТЕР ГЛУБИНОЙ ', msgarg:0, ' ФУТОВ.');
22: write('ЗАМЕЧАТЕЛЬНЫЙ УСПЕХ. КОМПЬЮТЕР ВАМ НЕ НУЖЕН.');
23: write('NАSА БУДЕТ ВЫЧИТАТЬ ', msgarg:0, ' $ ИЗ ВАШЕЙ ЗАРПЛАТЫ КАЖДУЮ НЕДЕЛЮ.');
24: write('ВАС ИСКЛЮЧИЛИ ИЗ СОСТАВА ЭКИПАЖА ДЛЯ ПОЛЕТА НА ЛУНУ.');
25: write('ВАС ИСКЛЮЧИЛИ ИЗ СОСТАВА ЭКИПАЖА НА ', msgarg:0, ' ПОЛЕТОВ НА ЛУНУ.')
_end;
writeln;
_);

_procedure getval(_var val: real);
_var i:integer;
_(
 i := 0;
 (a) _select 
  input@ = 'K': _goto 1;
  input@ = 'S': _( saved := frame@; get(input); _);
  input@ = 'T': _( get(input); interval := ord(input@); get(input); _goto a _);
  input@ = 'Y': _( get(input); verbose := true; _goto a _);
  input@ = 'R': _( frame@ := saved; get(input) _)
  _end;
  val := -1;
  _while (input@ <= '9') _do _(
    val := 0;
    i := 10*i + ord(input@);
    get(input);
  _);
  _if val = -1 _then
    landMsg(0)
  _else
    val := i;
_);
_procedure ending;
_(
  landMsg(1);
  code(э0620=,);
_);
_procedure update;
_(
 elapsed := elapsed + deltaT;
 remaining := remaining - deltaT;
 mass := mass - deltaT * value;
 altitude := newalt;
 Vmps := newVmps;
_);
_procedure P4250;
_(
 x := deltaT * value / mass;
 newVmps := (((lunarG * deltaT) + Vmps) - (LN(1.0 + x) * impulse));
 x2 := (x * x);
 x3 := (x2 * x);
 x4 := (x3 * x);
 x5 := (x4 * x);
  newalt := (((altitude - (((lunarG * deltaT) * deltaT) / (2.0))) - (Vmps * deltaT)) +
  ((impulse * deltaT) * (x/2.0 + x2/6.0 + x3/12.0 + x4/20.0 + x5/30.0)));
  _);

_procedure dead;
_(
 _if (ruined = 1) _then
  landMsg(7) (* splat *)
 _else _if (ruined < 6) _then
  landMsg( ruined ) (* oops again *)
 _else _( landMsg(6); (* enough already *)
   ending;
  _)
_);

_( (* landing *)
  frame := ref(cost);
  verbose := false;
  landMsg(8);
  _if eng _then BIND('WНАТ IS YOURS ? {172') _else BIND('ЧТО У ВАС ? {172');
  getval(value);
  _if _not (trunc(value) _IN [0..9]) _then value := 9.0;
  landMsg(9);
  fuel := round(15000 + value * 500);
  msgarg := ;
  landMsg(10);
  ruined := 0;
  (L4354) _(
    landMsg(11);
    interval := 10;
    elapsed := (0C);
    altitude := 120;
    Vmps := 1.0;
    mass := 32500;
    drymass := mass - fuel;
    lunarG := 1.0e-3;
    impulse := 1.8;
    saved := frame@;
  4410:
    write(round(elapsed):5, trunc(altitude):13);
    write(trunc((((altitude - (trunc(altitude))) * (5280)) + (0.5))):8);
    write(trunc((((5280) * Vmps) + (0.5))):9);
    write(round(((mass) - drymass)):13 );
  
    _if verbose _then write(Vmps * Vmps / altitude:0);
    writeln;
    (rate) _(
      _if eng _then
        BIND('FUEL RATE={172')
      _else
        BIND('РАСХОД={172');
      getval(value);
      _if ((value < 8.0) _or (value > 200)) _and (value <> 0.0) _then _(
        landMsg(12);
        _goto rate;
      _)
    _);
    (* 4466 *)
    _for cursec := 1 _to interval _do _(
      remaining := 1.0;
      (* L4472:,BSS,; *)
      (L4472) _if mass - drymass < 1.0e-3 _then _( (* else 4617 *)
        msgarg := round(elapsed);
        landMsg(12);
        deltaT := ((-(Vmps) + SQRT(((Vmps * Vmps) + ((2 * altitude) * lunarG)))) / lunarG);
        Vmps := ((lunarG * deltaT) + Vmps);
        elapsed := (elapsed + deltaT);
  4514:
        msgarg := round(elapsed);
        landMsg(14); (* on the Moon at ... sec *)
        Vfps := (5280 * Vmps);
        msgarg := round(Vfps);
        landMsg(15); (* impact velocity *)
        elapsed := mass - drymass;
        _if elapsed < 0.0 _then elapsed := 0.0;
        msgarg := round( elapsed );
        landMsg(16); (* fuel remaining *)
        _if Vfps <= 3 _then landMsg(17) (* perfect *)
        _else _if Vfps <= 15 _then landMsg(18) (* good *)
        _else _if Vfps <= 35 _then landMsg(19) (* no Buck Rogers *)
        _else _if Vfps <= 80 _then landMsg(20) (* heavy damage *)
        _else _(
          msgarg := trunc(0.19 * Vfps);
          landMsg(21); (* crater *)
          ruined := ruined + 1;
          dead;
        _);
        (* 4570 *)
        _if eng _then BIND('ТRY АGAIN (1) OR NOT (0) ? {172')
        _else BIND('ЕЩЕ РАЗ (1) ИЛИ ВСЕ (0) ? {172');

        _if (input@ <> '0') _then _goto L4354;
        _if (ruined = 0) _then landMsg(22)
        _else _(
          cost := (ruined * 34.23);
          msgarg := round( cost );
          landMsg(23);
          msgarg := ruined;
          _if (ruined = 1) _then landMsg(24) _else landMsg(25);
        _);
        ending;
      _) _else _if (remaining < (1.0e-3)) _then _exit L4472 _else _(
        deltaT := remaining;
        _if ((((deltaT) * value) + drymass) > mass) _then
          deltaT := (((mass) - drymass) / value);
        (* 4632 *)
        P4250;
        _if (newalt <= 0.0) _then
  4636: _(
          _if (deltaT < 5.0e-3) _then
            _goto 4514;
          deltaT := ((2.0 * altitude) / (SQRT(((Vmps * Vmps) + ((2.0 * altitude) * (lunarG - (((impulse) * value) / mass))))) + Vmps));
          P4250;
          update;
          _goto 4636;
        _);
        (* 4655 *)
        _if (Vmps <= 0.0) _then _(
          update;
          _goto L4472;
        _);
        _if (newVmps < 0.0) _then (L4664) _(
          Vfps := ((1.0 - ((mass * lunarG) / (impulse * value))) / 2.0);
          deltaT := (((mass * Vmps) / ((impulse * value) * (SQRT(((Vfps * Vfps) + (Vmps / impulse))) + Vfps))) + 0.05);
          P4250;  
          _if (newalt <= 0.0) _then
            _goto 4636;
          update;
          _if ((-newVmps > 0.0) _and (Vmps > 0.0)) _then _( _) _else _goto L4472;
          _goto L4664; 
        _) _else _(
          update;
          _goto L4472;
        _);
      _); (* 4472 if *)
    _); (* for *)
    _goto 4410;
  _); (* L4354 *)
  1: ending;
_); (* landing *)

_(
  _repeat
     bind('english / русский ?{172');
  _until (input@ = 'e') _or (input@ = 'p') _or (input@ = 'r');
  landing(input@ = 'e');
_).     
