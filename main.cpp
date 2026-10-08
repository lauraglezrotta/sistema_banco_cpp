#include <iostream>
#include <cmath>
#include <vector>
#include <cctype>
#include <iomanip>

using namespace std;

    //Estructura de datos principal
struct Tarjetas{
    string numero;
    int PIN;
    float saldo;
    bool bloqueada;
    float extracciones[12], depositos[12], saldosMensuales[12];
    };

int Menu()
{
    int opcion;
    cout << "============================================" << endl;
    cout << "---Marque la operacion que desea realizar---" << endl;
    cout << "============================================" << endl;
    cout << "1---Para Consultar Saldo." << endl;
    cout << "2---Para Depositar dinero." << endl;
    cout << "3---Para Extraer dinero." << endl;
    cout << "4---Para saber el total extraido en un a�o." << endl;
    cout << "5---Para saber el promedio mensual de transacciones en el ultimo a�o." << endl;
    cout << "6---Para saber los clientes equivalentes." << endl;
    cout << "7---Para saber la norma euclidiana de saldos." << endl;
    cout << "8---Para saber el mes de mayor actividad financiera." << endl;
    cout << "9---Para saber si dos clientes son ortogonales." << endl;
    cout << "10---Para saber el porcentaje de clientes con uso consistente." << endl;
    cout << "0---Para Salir.\n";
    cout << endl;
    cout << "Seleccione el numero de la operacion: ";
    cin >> opcion;
    cout << endl;

    return opcion;
}

bool ValidacionPINTarjeta(int PosicionTarjeta, int PINUM, vector<Tarjetas>& listaT)
{
    if(PINUM==listaT[PosicionTarjeta].PIN)
    return true;
    else
    return false;
}

bool FuncPIN(int PosicT, vector<Tarjetas>& listaT)
{
    int PINnum;

    while(true)
    {
    if(!(ValidacionPINTarjeta(PosicT, PINnum, listaT)))
    for (int j=7; j > 0; j--)
    {
    cout << "Diga su PIN de confirmacion (4 digitos): " << endl;
    cin >> PINnum;

    if(!(ValidacionPINTarjeta(PosicT, PINnum, listaT))){
    if(j>0)
    cout << "ERROR: Su PIN de tarjeta no es correspondiente, vuelva a intentarlo. (Quedan " << j-1 << " intentos)" << endl;
    }else
    return true;
    }
    cout << "Se ha quedado sin intentos! " << endl;
    listaT[PosicT].bloqueada=true;
    return false;
    }
}

int BusquedaTarjeta(string NUMTarjeta, vector<Tarjetas>& listaT)
{
    for(int i=0; i<listaT.size(); i++)
        {
            if(NUMTarjeta==listaT[i].numero)
            return i;
        }
        cout << "ERROR: Su numero de tarjeta no existe, vuelva a intentarlo." << endl;
        return -1;
}

    //Validar que el numero de tarjeta tenga 16 digitos
bool ValidacionNumeroTarjeta(string NumTarjeta)
{
    for(char c : NumTarjeta){
        if(c < '0' || c > '9'){
        cout << "ERROR: La tarjeta solo puede tener digitos" << endl;
        return false;
        }
    }
    if(NumTarjeta.size()==16)
    return true;
    else
    cout << "ERROR: Su numero de tarjeta debe tener 16 digitos, vuelva a intentarlo." << endl;
    return false;
}

int ComprobacionTarjeta(vector <Tarjetas>& listaT)
{
    string numeroTarjeta;

    do
    {
    cout << "Ingrese su numero de tarjeta magnetica: " << endl;
    cin >> numeroTarjeta;
    cout << endl;
    }while(!(ValidacionNumeroTarjeta(numeroTarjeta))|| BusquedaTarjeta(numeroTarjeta, listaT)==-1);

    int PosicionT=BusquedaTarjeta(numeroTarjeta, listaT);

    if(listaT[PosicionT].bloqueada)
    return -1;

    if(!(FuncPIN(PosicionT, listaT)))
    return -1;

    cout << endl;

    return PosicionT;
}

void FuncConsultarSaldo(vector<Tarjetas>& listaT)
{
    cout << "---CONSULTA DE SALDO---" << endl;

    int tarjeta=ComprobacionTarjeta(listaT);

    if(tarjeta==-1){
    cout << "ERROR: Tarjeta bloqueada, acuda a nuestra sucursal" << endl;
    return;
    }

    cout << fixed << setprecision(2) << "Su saldo es de: " << listaT[tarjeta].saldo << " CUP" << endl;
    cout << endl;
}

void FuncDepositarSaldo(vector<Tarjetas>& listaT)
{
    cout << "---DEPOSITACION DE SALDO---" << endl;

    int tarjeta=ComprobacionTarjeta(listaT);

    if(tarjeta==-1){
    cout << "ERROR: Tarjeta bloqueada, acuda a nuestra sucursal" << endl;
    return;
    }

    float dineroDepositar;

    do
    {
    cout << "Monto a depositar en CUP: ";
    cin >> dineroDepositar;

    if(dineroDepositar<0)
    cout << "ERROR: Valor invalido, vuelva a intentarlo" <<endl;
    }while(dineroDepositar<0);

    listaT[tarjeta].saldo+=dineroDepositar;
    cout << fixed << setprecision(2) << "Depositacion exitosa, Saldo actual: " << listaT[tarjeta].saldo << endl;
}

void FuncExtraerDinero(vector<Tarjetas>& listaT)
{
    cout << "---EXTRACCION DE SALDO---" << endl;

    int tarjeta=ComprobacionTarjeta(listaT);

    if(tarjeta==-1){
    cout << "ERROR: Tarjeta bloqueada, acuda a nuestra sucursal" << endl;
    return;
    }

    float Extraccion;

    do
    {
    do
    {
    cout << "Diga el Monto a extraer: ";
    cin >> Extraccion;

    if(Extraccion<0)
    cout << "ERROR: Valor invalido, vuelva a intentarlo" <<endl;
    }while(Extraccion<0);

    if(Extraccion>listaT[tarjeta].saldo)
    cout << "ERROR: La tarjeta ha depositar no tiene saldo suficiente, vuelva a intentarlo" << endl;
    }while(Extraccion>listaT[tarjeta].saldo);

    listaT[tarjeta].saldo-=Extraccion;
    cout << fixed << setprecision(2) << "Extraccion exitosa, Saldo actual: " << listaT[tarjeta].saldo << endl;
}

void FuncExtraccionXanio(vector<Tarjetas>& listaT)
{
    cout << "---EXTRACCIONES POR A�O---" << endl;

    int tarjeta=ComprobacionTarjeta(listaT);

    if(tarjeta==-1){
    cout << "ERROR: Tarjeta bloqueada, acuda a nuestra sucursal" << endl;
    return;
    }

    int valAbs, cifras, anio;
    do{
    do{
    cout << "Diga el a�o que desea saber su extraccion total" << endl;
    cin >> anio;

    valAbs=abs(anio);
    cifras=log10(valAbs) + 1;

    if(cifras!=4){
        cout << "ERROR: El a�o debe tener 4 cifras" << endl;
    }
    }while(cifras!=4);

    if(anio<=1996 || anio>=2025)
        cout << "ERROR: La Institucion Metropolitana solo tiene registro desde 1996 hasta 2025" << endl;
    }while(anio<=1996 || anio>=2025);

    float ExtraccionesAnio;

    for(int i=0; i<12; i++){
    ExtraccionesAnio += listaT[tarjeta].extracciones[i];
    }

    cout << "El total de extracciones que realiz� en el a�o " << anio << " fue de " << fixed << setprecision(2) << ExtraccionesAnio << " CUP";
    cout << endl;
}

void FuncPromedioXmesUltimAnio(vector<Tarjetas>& listaT)
{
    cout << "---PROMEDIO DE TRANSACCIONES EN EL ULTIMO A�O---" << endl;

    int tarjeta=ComprobacionTarjeta(listaT);

    if(tarjeta==-1){
    cout << "ERROR: Tarjeta bloqueada, acuda a nuestra sucursal" << endl;
    return;
    }

    float promedio;

    for(int i=0; i<12; i++){
    promedio += 2/(listaT[tarjeta].extracciones[i]+listaT[tarjeta].depositos[i]);
    }

    cout << fixed << setprecision(3) << "El promedio mensual de transacciones en el ultimo a�o es de " << promedio << endl;
    cout << endl;
}

void FuncGruposEquivalentes(vector<Tarjetas>& listaT)
{
    cout << "---CLIENTES EQUIVALENTES---" << endl;
    cout << endl;

    vector<float> promedioMensual;

    for(int j=0; j<listaT.size(); j++){
    float ValorSumado=0;
    for(int i=0; i<12; i++){
    float ValorUnitario = (2/(listaT[j].extracciones[i]+listaT[j].depositos[i]));
    ValorSumado += ValorUnitario;
    }
    promedioMensual.push_back(ValorSumado);
    }

    vector<string> grupos;
    for(int j=0; j<listaT.size(); j++){
    for(int i=0; i<listaT.size(); i++){

        if((j!=i)&&(j<i)){
        float diferencia = promedioMensual[j]-promedioMensual[i];
        float suma = promedioMensual[j]+promedioMensual[i];
        float porcentaje = suma/10;         //10 por ciento

        if(porcentaje>=diferencia){
        grupos.push_back(listaT[j].numero + " y " + listaT[i].numero);
        }
        }
    }
    }
    cout << "Grupos de clientes equivalentes: " << endl;
    cout << endl;
    for(int k=0; k<grupos.size(); k++){
        cout << "Grupo " << k+1 << ": Tarjetas: " << grupos[k] << endl;
    }
    cout << endl;
}

void FuncNormaEuclidea(vector<Tarjetas>& listaT)
{
    cout << "---NORMA EUCLIDIANA DE SALDOS---" << endl;
    cout << endl;

    int tarjeta=ComprobacionTarjeta(listaT);

    if(tarjeta==-1){
    cout << "ERROR: Tarjeta bloqueada, acuda a nuestra sucursal" << endl;
    return;
    }

    float sumaCuadrados =0;

    for(int i=0; i< 12; i++){

        float saldo = listaT[tarjeta].saldosMensuales[i];
        sumaCuadrados += saldo * saldo;
    }
    float norma = sqrt(sumaCuadrados);
    cout << fixed << setprecision(2) << "La norma euclidiana de los saldos mensuales de su tarjeta es: " << norma << " CUP" << endl;
}

void FuncMesMayorAct(vector<Tarjetas>& listaT)
{
    cout << "---MES DE MAYOR ACTIVIDAD FINANCIERA---" << endl;
    cout << endl;
    int mayor = -1, MES;
    float sumaTrans;
    float transXmes[12];

    for(int i = 0; i < 12; i ++){
    for(int j= 0; j < listaT.size(); j ++){
        sumaTrans += listaT[j].extracciones[i]+listaT[j].depositos[i];
    }
        transXmes[i]=sumaTrans;
    if (transXmes[i] > mayor){
        mayor = sumaTrans;
        MES=i;
    }
    }
    string meses[12] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
    cout << "El mes de mayor actividad del banco es: " << meses[MES] << endl;
}

void FuncClientesOrtogonales(vector<Tarjetas>& listaT)
{
    cout << "---CLIENTES ORTOGONALES---" << endl;
    cout << endl;
    string cliente1, cliente2;

    do{
    do{
    cout << "Diga la tarjeta del primer cliente: " << endl;
    cin >> cliente1;
    cout << endl;
    }while(!(ValidacionNumeroTarjeta(cliente1))||BusquedaTarjeta(cliente1, listaT)=='a');
    do{
    cout<< "Diga la tarjeta del segundo cliente: " << endl;
    cin >> cliente2;
    cout << endl;
    }while(!(ValidacionNumeroTarjeta(cliente2))||BusquedaTarjeta(cliente2, listaT)=='a');

    if(cliente1==cliente2)
    cout << "ERROR: Las tarjetas de los clientes deben ser diferentes, vuelva a intentarlo." << endl;

    }while(cliente1==cliente2);

    int indice1 = BusquedaTarjeta(cliente1, listaT);
    int indice2 = BusquedaTarjeta(cliente2, listaT);

    vector<double> VectPromedio1(12, 0), VectPromedio2(12, 0);

    double ProductoEscalar=0;

    for(int i=0; i<12; i++){
    VectPromedio1[i] = (2/(listaT[indice1].extracciones[i]+listaT[indice1].depositos[i]));
    VectPromedio2[i] = (2/(listaT[indice2].extracciones[i]+listaT[indice2].depositos[i]));

    ProductoEscalar += VectPromedio1[i] * VectPromedio2[i];
    }

    if(ProductoEscalar==0)
        cout << "Los clientes son ortogonales, sus patrones de uso son independientes. " << endl;
    else
        cout << "Los clientes NO son ortogonales, sus patrones de uso NO son independientes. " << endl;

    cout << fixed << setprecision(5) << "El Producto escalar es: " << ProductoEscalar << endl;
    cout << endl;
}

void FuncUsoConsistente(vector<Tarjetas>& listaT) {
    int count = 0;

    // cout << "lista t size: " << listaT.size() << endl;

    for (int j = 0; j < listaT.size(); j++)
    {
        float media = 0.0;
        for (int i = 0; i < 6; i++)
        {
            media += listaT[j].extracciones[6 + i] + listaT[j].depositos[6 + i];
        }
        media = media / 6;

        // cout << "media de " << j << ": " << media << endl;
        
        float cuadrados = 0.0;
        for (int i = 0; i < 6; i++)
        {
            float v = listaT[j].extracciones[6 + i] + listaT[j].depositos[6 + i];
            cuadrados += (v - media) * (v - media);
        }
        float devEstandar = sqrt(cuadrados / 6);
        
        // cout << "desviacion estandar de " << j << ": " << devEstandar << endl;
        
        float coeficienteVariacion = 0.0;
        if (media != 0){
            coeficienteVariacion = devEstandar / media * 100.0;
        }

        // cout << "coeficiente de variacion de " << j << ": " << coeficienteVariacion << endl;
        
        if (coeficienteVariacion < 15) count++;
        
        // cout << "count de " << j << ": " << count << endl;
        
    }
    
    cout << "listaT size: " << listaT.size() << endl;
    cout << "Porcentaje de tarjetas con uso consistente: " << fixed << setprecision(2) << count /  (float)listaT.size()  * 100.0  << " %" << endl;
    
}




int main()
{
    vector<Tarjetas> listaTarjetas;
    listaTarjetas.push_back({"9207959879859465", 1111, 1000.00, false, 1000.0, 200, 3000, 400.60, 50, 600, 700.80, 800, 900, 1900, 1100, 1200, 7090, 280, 3000, 4070, 5060, 6500, 7010, 8200, 9030, 1050, 1160, 1200, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200});
    //listaTarjetas.push_back({"9207959879859465", 1111, 1000.00, false, 1000.0, 200, 3000, 400.60, 50, 600, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700.80, 700, 800, 900, 1000, 1100, 1200});
    listaTarjetas.push_back({"9123456789012345", 1234, 23000.00, false, 1101, 210, 310, 410, 510, 610, 9010, 810, 910, 1010, 1110, 1210, 1000, 210, 310, 410, 510, 610, 710, 810, 910, 1010, 1110, 1210, 110, 210, 310, 410, 510, 610, 710, 810, 910, 1010, 1110, 1210});
    listaTarjetas.push_back({"9378282246310008", 2222, 12001.78, false, 1200, 220, 320, 420, 520, 620, 720, 820, 920, 1020, 1120, 1220, 1020, 2720, 320, 420, 520, 620, 720, 820, 920, 1020, 1120, 1220, 120, 220, 320, 420, 520, 620, 720, 820, 920, 1020, 1120, 1220});
    listaTarjetas.push_back({"9601112345678905", 2332, 22200.10, false, 3000, 3000, 3000, 3000, 3530, 3630, 3730, 3830, 3930, 3030, 3130, 3230, 3060, 360, 360, 360, 360, 360, 360, 360, 360.60, 360, 360, 360, 130, 230, 330, 430, 530, 630, 730, 830, 930, 1030, 1130, 1230});
    listaTarjetas.push_back({"9999999999999998", 9999, 6000.50, false, 1040, 2040, 3040, 4400, 5940, 6470, 7410, 840, 9002.40, 1040, 1014.0, 1240, 1040, 2040, 3040, 4040, 5090, 609.40, 7040, 8040, 9040, 10040, 11040, 10240, 140, 240, 340, 440, 540, 640, 740, 840, 940, 1040, 1140, 1240});
    listaTarjetas.push_back({"9111111111111111", 2909, 9000.70, false, 150, 250, 35.00, 450, 550, 6880, 750, 85.0, 950, 1050, 1150, 1250, 150, 250, 350, 450, 550, 650, 750, 850, 950, 1050, 1150, 1250, 150, 250, 350, 450, 550, 650, 750, 850, 950, 1050, 1150, 1250});
    listaTarjetas.push_back({"9550000000000001", 6756, 200.00, false, 1600, 260, 360, 460, 560, 660, 760, 860, 960, 1060, 1160, 1260, 160, 260, 360, 460, 5060, 660, 760, 860, 960, 1060, 1160, 1260, 160, 260, 360, 460, 560, 660, 760, 860, 960, 1060, 1160, 1260});
    listaTarjetas.push_back({"9371449635398434", 3456, 120.90, false, 1450, 270, 379.90, 4070, 570, 670, 7070, 870, 970.90, 1070, 1170, 1270, 170, 270, 3760, 470, 570, 670, 770, 870, 970, 1070, 1170, 1270, 170, 270, 370, 470, 570, 670, 770, 870, 970, 1070, 1170, 1270});
    listaTarjetas.push_back({"9352835439437904", 2225, 2345.50, false, 2000, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 1080, 220, 110, 180, 50, 1000, 700, 200, 180, 100, 190, 100, 180, 280, 380, 480, 580, 680, 780, 880, 980, 1080, 1180, 1280});
    listaTarjetas.push_back({"9543111111111114", 9909, 1777.80, false, 1009, 209, 309, 409, 500, 600, 700, 180, 109, 190, 100, 108, 1900, 290, 160, 490, 590, 690, 790, 890, 190, 267, 178, 120, 190, 290, 390, 490, 590, 690, 790, 890, 990, 1090, 1190, 1290});

    cout << "===================================================" << endl;
    cout << "---Bienvenido al Sistema del Banco Metropolitano---" << endl;
    cout << "===================================================" << endl;

    int opcion;
    do
    {
    opcion=Menu();
    switch(opcion)
    {
    case 1:
        FuncConsultarSaldo(listaTarjetas);
        break;
    case 2:
        FuncDepositarSaldo(listaTarjetas);
        break;
    case 3:
        FuncExtraerDinero(listaTarjetas);
        break;
    case 4:
        FuncExtraccionXanio(listaTarjetas);
        break;
    case 5:
        FuncPromedioXmesUltimAnio(listaTarjetas);
        break;
    case 6:
        FuncGruposEquivalentes(listaTarjetas);
        break;
    case 7:
        FuncNormaEuclidea(listaTarjetas);
        break;
    case 8:
        FuncMesMayorAct(listaTarjetas);
        break;
    case 9:
        FuncClientesOrtogonales(listaTarjetas);
        break;
    case 10:
        FuncUsoConsistente(listaTarjetas);
        break;
    case 0:
        break;
    default:
        cout << "Valor invalido, vuelva a intentarlo" << endl;
        break;
    }

    }while(opcion!=0);

    cout << "Gracias por usar el Sistema del Banco Metropolitano" << endl;
    return 0;
}

