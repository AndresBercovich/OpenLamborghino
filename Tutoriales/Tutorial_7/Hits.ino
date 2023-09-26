


int umbral = 700;
int geo = 0;

int HL, HR = 0;

void Read_hits() {

  HL = analogRead(A7);
  HR = analogRead(A0);

  if (HL > umbral) {
    HL = 0;
  } else {
    HL = 1;
  }

  if (HR > umbral) {
    HR = 0;
  } else {
    HR = 1;
  }
}

void detectGeo() {

  Read_hits();


  if ((HL == 0) && (HR == 0)) {
    geo = 0;
  }

  if ((HL == 1) && (HR == 0)) {
    geo = 1;
  }

  if ((HL == 0) && (HR == 1)) {
    geo = 2;
  }

  if ((HL == 1) && (HR == 1)) {
    geo = 3;
  }

if (l_geo !=geo) {

if (geo == 0 && l_geo == 2 && ll_geo == 0) {

  funcion_HL();

}
if (geo == 0 && l_geo == 1 && ll_geo == 0) {

  funcion_HR();

}

if (geo == 0 && ((l_geo == 3) || (ll_geo == 3) || (lll_geo == 3))){

  funcion_Cruce();

}
lll_geo = ll_geo;
ll_geo = l_geo;
l_geo = geo;

}



}
