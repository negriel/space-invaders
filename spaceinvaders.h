//=========================================================
typedef struct TNave Nave;
typedef struct TMonstro Monstro;
typedef struct TTiro Tiro;

//=========================================================
void carregaTexturas();

//=========================================================
Nave* nave_cria(int x, int y);
void nave_destroi(Nave *nave);
int nave_vivo(Nave *nave);
void nave_desenha(Nave *nave);
void nave_movimenta(Nave *nave, int direcao);

////=========================================================
Monstro* monstro_cria(int x, int y);
void monstro_destroi(Monstro *monst);
void monstro_movimenta(Monstro *monst, int direcao);
void monstro_desenha(Monstro *monst, int tipo);

///==========================================================
Tiro* tiro_cria(int x, int y);
void tiro_dispara(Tiro *tiro);
void tiro_desenha(Tiro *tiro);
void tiro_movimenta(Tiro *tiro);


