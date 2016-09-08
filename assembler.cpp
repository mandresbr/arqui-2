#include "assembler.h"
#include "ui_assembler.h"

typedef std::map<std::string, std::string> stringmap;
typedef std::map<std::string, int> strintmap;
typedef std::map<std::string, std::string>::iterator it;


Assembler::Assembler(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Assembler)
{
    ui->setupUi(this);
}

Assembler::~Assembler()
{
    delete ui;
}

// funcion que retorna un vector de tokens de una cadena

std::vector<std::string> GetWords(std::string instruc)
{
    std::vector<std::string> words;
    char *inst = strdup(instruc.c_str());
    char *token=strtok(inst," :,()[]+");
    while (token != NULL)
    {
        qDebug() << token;
        words.push_back(token);
        token = strtok (NULL, " :,()[]+");
    }
    return words;
}

/*  se traduce de una cadena de von neumann a binario */
QString translate(QString trans){

    stringmap opcode;

    opcode["add0"] = "0000000";
    opcode["add1"] = "0000001";
    opcode["add2"] = "0000010";
    opcode["add3"] = "0000011";
    opcode["add4"] = "0000100";
    opcode["add5"] = "0000101";
    opcode["add6"] = "0000110";
    opcode["sub7"] = "0000111";
    opcode["sub8"] = "0001000";
    opcode["sub9"] = "0001001";
    opcode["sub10"] = "0001010";
    opcode["sub11"] = "0001011";
    opcode["sub12"] = "0001100";
    opcode["sub13"] = "0001101";
    opcode["and14"] = "0001110";
    opcode["and15"] = "0001111";
    opcode["and16"] = "0010000";
    opcode["and17"] = "0010001";
    opcode["and18"] = "0010010";
    opcode["and19"] = "0010011";
    opcode["and20"] = "0010100";
    opcode["or21"] = "0010101";
    opcode["or22"] = "0010110";
    opcode["or23"] = "0010111";
    opcode["or24"] = "0011000";
    opcode["or25"] = "0011001";
    opcode["or26"] = "0011010";
    opcode["or27"] = "0011011";
    opcode["mul28"] = "0011100";
    opcode["mul29"] = "0011101";
    opcode["mul30"] = "0011110";
    opcode["mul31"] = "0011111";
    opcode["mul32"] = "0100000";
    opcode["mul33"] = "0100001";
    opcode["mul34"] = "0100010";
    opcode["div35"] = "0100011";
    opcode["div36"] = "0100100";
    opcode["div37"] = "0100101";
    opcode["div38"] = "0100110";
    opcode["div39"] = "0100111";
    opcode["div40"] = "0101000";
    opcode["div41"] = "0101001";
    opcode["mov42"] = "0101010";
    opcode["mov43"] = "0101011";
    opcode["mov44"] = "0101100";
    opcode["mov45"] = "0101101";
    opcode["mov46"] = "0101110";
    opcode["mov47"] = "0101111";
    opcode["mov48"] = "0110000";
    opcode["brm49"] = "0110001";
    opcode["bri50"] = "0110010";
    opcode["brme5"] = "0110011";
    opcode["shl52"] = "0110100";
    opcode["shr53"] = "0110101";
    opcode["nop54"] = "0110110";
    opcode["jump55"] = "0110111";
    opcode["add56"] = "0111000";
    opcode["add57"] = "0111001";
    opcode["add58"] = "0111010";
    opcode["add59"] = "0111011";
    opcode["sub60"] = "0111100";
    opcode["sub61"] = "0111101";
    opcode["sub62"] = "0111110";
    opcode["sub63"] = "0111111";
    opcode["and64"] = "1000000";
    opcode["and65"] = "1000001";
    opcode["and66"] = "1000010";
    opcode["and67"] = "1000011";
    opcode["or68"] = "1000100";
    opcode["or69"] = "1000101";
    opcode["or70"] = "1000110";
    opcode["or71"] = "1000111";
    opcode["mul72"] = "1001000";
    opcode["mul73"] = "1001001";
    opcode["mul74"] = "1001010";
    opcode["mul75"] = "1001011";
    opcode["div76"] = "1001100";
    opcode["div77"] = "1001101";
    opcode["div78"] = "1001110";
    opcode["div79"] = "1001111";
    opcode["mov80"] = "1010000";
    opcode["mov81"] = "1010001";
    opcode["mov82"] = "1010010";
    opcode["mov83"] = "1010011";
    opcode["mov84"] = "1010100";
    opcode["add85"] = "1010101";
    opcode["sub86"] = "1010110";
    opcode["mul87"] = "1010111";
    opcode["div88"] = "1011000";
    opcode["and89"] = "1011001";
    opcode["or90"] = "1011010";

    stringmap registros;

    registros["R1"] = "000";
    registros["R2"] = "001";
    registros["R3"] = "010";
    registros["R4"] = "011";
    registros["R5"] = "100";
    registros["R6"] = "101";
    registros["R7"] = "110";
    registros["R8"] = "111";

    stringmap constante;

    constante["0"] = "000";
    constante["1"] = "001";
    constante["2"] = "010";
    constante["3"] = "011";
    constante["4"] = "100";
    constante["5"] = "101";
    constante["6"] = "110";
    constante["7"] = "111";


    std::vector<std::vector<std::string> > formato; /* contenedor del vector de tokens de la cadena de
                                                    instrucciones */


    int formato_size;
    std::string text_out = "";

    std::string instruction;
    QString instruc;
    QTextStream in(&trans);
    instruc=in.readLine();
    qDebug() << instruc;
    while( instruc != NULL)
    {
        instruction = instruc.toStdString();
        formato.push_back(GetWords(instruction));
        instruc=in.readLine();
    }


    formato_size = formato.size();

    // ADD REGEX
    QRegularExpression regex0("ADD R[0-8],( |){1,}R[0-8]");
    QRegularExpression regex1("ADD R[0-8],( |)[0-8]");
    QRegularExpression regex2("ADD \\[R[0-8]],( |)R[0-8]");
    QRegularExpression regex3("ADD \\[R[0-8]\\+[0-8]], R[0-8]");
    QRegularExpression regex4("ADD R[0-8],( |)\\[R[0-8]]");
    QRegularExpression regex5("ADD R[0-8],( |)\\[R[0-8]\\+[0-8]");
    QRegularExpression regex6("ADD \\[R[[0-8]],( |)\\[R[0-8]]");
    // SUB REGEX
    QRegularExpression regex7("SUB R[0-8],( |)R[0-8]");
    QRegularExpression regex8("SUB R[0-8],( |)[0-8]");
    QRegularExpression regex9("SUB \\[R[0-8]],( |)R[0-8]");
    QRegularExpression regex10("SUB \\[R[0-8]\\+[0-8]],( |)R[0-8]");
    QRegularExpression regex11("SUB R[0-8],( |)\\[R[0-8]]");
    QRegularExpression regex12("SUB R[0-8],( |)\\[R[0-8]\\+[0-8]");
    QRegularExpression regex13("SUB \\[R[[0-8]],( |)\\[R[0-8]]");

    // AND REGEX
    QRegularExpression regex14("AND R[0-8],( |)R[0-8]");
    QRegularExpression regex15("AND R[0-8],( |)[0-8]");
    QRegularExpression regex16("AND \\[R[0-8]],( |)R[0-8]");
    QRegularExpression regex17("AND \\[R[0-8]\\+[0-8]],( |)R[0-8]");
    QRegularExpression regex18("AND R[0-8],( |)\\[R[0-8]]");
    QRegularExpression regex19("AND R[0-8],( |)\\[R[0-8]\\+[0-8]");
    QRegularExpression regex20("AND \\[R[[0-8]],( |)\\[R[0-8]]");

    // OR REGEX
    QRegularExpression regex21("OR R[0-8],( |)R[0-8]");
    QRegularExpression regex22("OR R[0-8],( |)[0-8]");
    QRegularExpression regex23("OR \\[R[0-8]],( |)R[0-8]");
    QRegularExpression regex24("OR \\[R[0-8]\\+[0-8]],( |)R[0-8]");
    QRegularExpression regex25("OR R[0-8],( |)\\[R[0-8]]");
    QRegularExpression regex26("OR R[0-8],( |)\\[R[0-8]\\+[0-8]");
    QRegularExpression regex27("OR \\[R[[0-8]],( |)\\[R[0-8]]");

    // MUL REGEX
    QRegularExpression regex28("MUL R[0-8],( |)R[0-8]");
    QRegularExpression regex29("MUL R[0-8],( |)[0-8]");
    QRegularExpression regex30("MUL \\[R[0-8]],( |)R[0-8]");
    QRegularExpression regex31("MUL \\[R[0-8]\\+[0-8]],( |)R[0-8]");
    QRegularExpression regex32("MUL R[0-8],( |)\\[R[0-8]]");
    QRegularExpression regex33("MUL R[0-8],( |)\\[R[0-8]\\+[0-8]");
    QRegularExpression regex34("MUL \\[R[[0-8]],( |)\\[R[0-8]]");

    // DIV REGEX
    QRegularExpression regex35("DIV R[0-8],( |)R[0-8]");
    QRegularExpression regex36("DIV R[0-8],( |)[0-8]");
    QRegularExpression regex37("DIV \\[R[0-8]],( |)R[0-8]");
    QRegularExpression regex38("DIV \\[R[0-8]\\+[0-8]],( |)R[0-8]");
    QRegularExpression regex39("DIV R[0-8],( |)\\[R[0-8]]");
    QRegularExpression regex40("DIV R[0-8],( |)\\[R[0-8]\\+[0-8]");
    QRegularExpression regex41("DIV \\[R[[0-8]],( |)\\[R[0-8]]");

    // MOV REGEX
    QRegularExpression regex42("MOV R[0-8],( |)R[0-8]");
    QRegularExpression regex43("MOV R[0-8],( |)[0-8]");
    QRegularExpression regex44("MOV \\[R[0-8]], R[0-8]");
    QRegularExpression regex45("MOV \\[R[0-8]\\+[0-8]], R[0-8]");
    QRegularExpression regex46("MOV R[0-8], \\[R[0-8]]");
    QRegularExpression regex47("MOV R[0-8], \\[R[0-8]\\+[0-8]");
    QRegularExpression regex48("MOV \\[R[[0-8]], \\[R[0-8]]");

    // BRM REGEX
    QRegularExpression regex49("BRM R[0-8], R[0-8], \\w+");
    // BRI REGEX
    QRegularExpression regex50("BRI R[0-8], R[0-8], \\w+");
    // BRME REGEX
    QRegularExpression regex51("BRME R[0-8], R[0-8], \\w+");
    // SHL REGEX
    QRegularExpression regex52("SHL R[0-8], R[0-8], [0-8]");
    // SHR REGEX
    QRegularExpression regex53("SHR R[0-8], R[0-8], [0-8]");
    // NOP REGEX
    QRegularExpression regex54("NOP");
    // JUMP REGEX
    QRegularExpression regex55("JUMP \\w+");


    // SEGUNDOS ADD
    QRegularExpression regex56("ADD R[0-8], \\[[0-8]]");
    QRegularExpression regex57("ADD \\[R[0-8]], \\[[0-8]]");
    QRegularExpression regex58("ADD \\[[0-8]], R[0-8]");
    QRegularExpression regex59("ADD \\[[0-8], \\[R[0-8]]");

    // SEGUNDOS SUB
    QRegularExpression regex60("SUB R[0-8], \\[[0-8]]");
    QRegularExpression regex61("SUB \\[R[0-8]], \\[[0-8]]");
    QRegularExpression regex62("SUB \\[[0-8]], R[0-8]");
    QRegularExpression regex63("SUB \\[[0-8], \\[R[0-8]]");

    // SEGUNDOS AND
    QRegularExpression regex64("AND R[0-8], \\[[0-8]]");
    QRegularExpression regex65("AND \\[R[0-8]], \\[[0-8]]");
    QRegularExpression regex66("AND \\[[0-8]], R[0-8]");
    QRegularExpression regex67("AND \\[[0-8], \\[R[0-8]]");

    // SEGUNDOS OR
    QRegularExpression regex68("OR R[0-8], \\[[0-8]]");
    QRegularExpression regex69("OR \\[R[0-8]], \\[[0-8]]");
    QRegularExpression regex70("OR \\[[0-8]], R[0-8]");
    QRegularExpression regex71("OR \\[[0-8], \\[R[0-8]]");

    // SEGUNDOS MUL
    QRegularExpression regex72("MUL R[0-8], \\[[0-8]]");
    QRegularExpression regex73("MUL \\[R[0-8]], \\[[0-8]]");
    QRegularExpression regex74("MUL \\[[0-8]], R[0-8]");
    QRegularExpression regex75("MUL \\[[0-8], \\[R[0-8]]");

    // SEGUNDOS DIV
    QRegularExpression regex76("DIV R[0-8], \\[[0-8]]");
    QRegularExpression regex77("DIV \\[R[0-8]], \\[[0-8]]");
    QRegularExpression regex78("DIV \\[[0-8]], R[0-8]");
    QRegularExpression regex79("DIV \\[[0-8], \\[R[0-8]]");

    // SEGUNDOS MOV
    QRegularExpression regex80("MOV R[0-8], \\[[0-8]]");
    QRegularExpression regex81("MOV \\[R[0-8]], \\[[0-8]]");
    QRegularExpression regex82("MOV \\[[0-8]], R[0-8]");
    QRegularExpression regex83("MOV \\[[0-8], \\[R[0-8]]");

    // ULTIMO MOV
    QRegularExpression regex84("MOV \\[R[0-8]\\+[0-8]], \\[R[0-8]]");
    // ULTIMO ADD
    QRegularExpression regex85("ADD \\[R[0-8]\\+[0-8]], \\[R[0-8]]");
    // ULTIMO SUB
    QRegularExpression regex86("SUB \\[R[0-8]\\+[0-8]], \\[R[0-8]]");
    // ULTIMO MUL
    QRegularExpression regex87("MUL \\[R[0-8]\\+[0-8]], \\[R[0-8]]");
    // ULTIMO DIV
    QRegularExpression regex88("DIV \\[R[0-8]\\+[0-8]], \\[R[0-8]]");
    // ULTIMO AND
    QRegularExpression regex89("AND \\[R[0-8]\\+[0-8]], \\[R[0-8]]");
    // ULTIMO OR
    QRegularExpression regex90("OR \\[R[0-8]\\+[0-8]], \\[R[0-8]]");

    QTextStream in1(&trans);
    std::string temp;

    /* se recorre el contenedor de los tokens para saber cual instrucción
            se esta trabajando del archivo o el textedit y asi se asigna el formato en binario correspondiente*/
    for (int i = 0; i < formato_size; ++i)
    {
        QString line = in1.readLine();
        qDebug() << line;
        if(regex0.match(line).hasMatch())
            temp = "add0";
        else if(regex1.match(line).hasMatch())
            temp = "add1";
        else if(regex2.match(line).hasMatch())
            temp = "add2";
        else if(regex3.match(line).hasMatch())
            temp = "add3";
        else if(regex4.match(line).hasMatch())
            temp = "add4";
        else if(regex5.match(line).hasMatch())
            temp = "add5";
        else if(regex6.match(line).hasMatch())
            temp = "add6";
        else if(regex7.match(line).hasMatch())
            temp = "sub7";
        else if(regex8.match(line).hasMatch())
            temp = "sub8";
        else if(regex9.match(line).hasMatch())
            temp = "sub9";
        else if(regex10.match(line).hasMatch())
            temp = "sub10";
        else if(regex11.match(line).hasMatch())
            temp = "sub11";
        else if(regex12.match(line).hasMatch())
            temp = "sub12";
        else if(regex13.match(line).hasMatch())
            temp = "sub13";
        else if(regex14.match(line).hasMatch())
            temp = "and14";
        else if(regex15.match(line).hasMatch())
            temp = "and15";
        else if(regex16.match(line).hasMatch())
            temp = "and16";
        else if(regex17.match(line).hasMatch())
            temp = "and17";
        else if(regex18.match(line).hasMatch())
            temp = "and18";
        else if(regex19.match(line).hasMatch())
            temp = "and19";
        else if(regex20.match(line).hasMatch())
            temp = "and20";
        else if(regex21.match(line).hasMatch())
            temp = "or21";
        else if(regex22.match(line).hasMatch())
            temp = "or22";
        else if(regex23.match(line).hasMatch())
            temp = "or23";
        else if(regex24.match(line).hasMatch())
            temp = "or24";
        else if(regex25.match(line).hasMatch())
            temp = "or25";
        else if(regex26.match(line).hasMatch())
            temp = "or26";
        else if(regex27.match(line).hasMatch())
            temp = "or27";
        else if(regex28.match(line).hasMatch())
            temp = "mul28";
        else if(regex29.match(line).hasMatch())
            temp = "mul29";
        else if(regex30.match(line).hasMatch())
            temp = "mul30";
        else if(regex31.match(line).hasMatch())
            temp = "mul31";
        else if(regex32.match(line).hasMatch())
            temp = "mul32";
        else if(regex33.match(line).hasMatch())
            temp = "mul33";
        else if(regex34.match(line).hasMatch())
            temp = "mul34";
        else if(regex35.match(line).hasMatch())
            temp = "div35";
        else if(regex36.match(line).hasMatch())
            temp = "div36";
        else if(regex37.match(line).hasMatch())
            temp = "div37";
        else if(regex38.match(line).hasMatch())
            temp = "div38";
        else if(regex39.match(line).hasMatch())
            temp = "div39";
        else if(regex40.match(line).hasMatch())
            temp = "div40";
        else if(regex41.match(line).hasMatch())
            temp = "div41";
        else if(regex42.match(line).hasMatch())
            temp = "mov42";

        else if(regex43.match(line).hasMatch())
            temp = "mov43";
        else if(regex44.match(line).hasMatch())
            temp = "mov44";
        else if(regex45.match(line).hasMatch())
            temp = "mov45";
        else if(regex46.match(line).hasMatch())
            temp = "mov46";
        else if(regex46.match(line).hasMatch())
            temp = "mov47";
        else if(regex47.match(line).hasMatch())
            temp = "mov47";
        else if(regex48.match(line).hasMatch())
            temp = "mov48";
        else if(regex49.match(line).hasMatch())
            temp = "brm49";
        else if(regex50.match(line).hasMatch())
            temp = "bri50";
        else if(regex51.match(line).hasMatch())
            temp = "brme51";
        else if(regex52.match(line).hasMatch())
            temp = "shl52";
        else if(regex53.match(line).hasMatch())
            temp = "shr53";
        else if(regex54.match(line).hasMatch())
            temp = "nop54";
        else if(regex55.match(line).hasMatch())
            temp = "jump55";
        else if(regex56.match(line).hasMatch())
            temp = "add56";
        else if(regex57.match(line).hasMatch())
            temp = "add57";
        else if(regex58.match(line).hasMatch())
            temp = "add58";
        else if(regex59.match(line).hasMatch())
            temp = "add59";
        else if(regex60.match(line).hasMatch())
            temp = "sub60";
        else if(regex61.match(line).hasMatch())
            temp = "sub61";
        else if(regex62.match(line).hasMatch())
            temp = "sub62";
        else if(regex63.match(line).hasMatch())
            temp = "sub63";
        else if(regex64.match(line).hasMatch())
            temp = "and64";
        else if(regex65.match(line).hasMatch())
            temp = "and65";
        else if(regex66.match(line).hasMatch())
            temp = "and66";
        else if(regex67.match(line).hasMatch())
            temp = "and67";
        else if(regex68.match(line).hasMatch())
            temp = "or68";
        else if(regex69.match(line).hasMatch())
            temp = "or69";
        else if(regex70.match(line).hasMatch())
            temp = "or70";
        else if(regex71.match(line).hasMatch())
            temp = "or71";
        else if(regex72.match(line).hasMatch())
            temp = "mul72";
        else if(regex73.match(line).hasMatch())
            temp = "mul73";
        else if(regex74.match(line).hasMatch())
            temp = "mul74";
        else if(regex75.match(line).hasMatch())
            temp = "mul75";
        else if(regex76.match(line).hasMatch())
            temp = "div76";
        else if(regex77.match(line).hasMatch())
            temp = "div77";
        else if(regex78.match(line).hasMatch())
            temp = "div78";
        else if(regex79.match(line).hasMatch())
            temp = "div79";
        else if(regex80.match(line).hasMatch())
            temp = "mov80";
        else if(regex81.match(line).hasMatch())
            temp = "mov81";
        else if(regex82.match(line).hasMatch())
            temp = "mov82";
        else if(regex83.match(line).hasMatch())
            temp = "mov83";
        else if(regex84.match(line).hasMatch())
            temp = "mov84";
        else if(regex85.match(line).hasMatch())
            temp = "add85";
        else if(regex86.match(line).hasMatch())
            temp = "sub86";
        else if(regex87.match(line).hasMatch())
            temp = "mul87";
        else if(regex88.match(line).hasMatch())
            temp = "div88";
        else if(regex89.match(line).hasMatch())
            temp = "and89";
        else if(regex90.match(line).hasMatch())
            temp = "or90";
        else
            temp = "xxxxxxxx";


        qDebug() << QString::fromStdString(temp);
        std::string linea = opcode[temp];
        // ADD
        if (linea == "0000000")
        {
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0000001")
        {
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0000010"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0000011"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][3]];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0000100"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0000101"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante[formato[i][3]];
        }
        else if (linea == "0000110"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }

        // SUB

        else if (linea == "0000111"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0001000"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0001001"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0001010"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][3]];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0001011"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0001100"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante[formato[i][3]];
        }
        else if (linea == "0001101"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }

        // AND

        else if (linea == "0001110"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0001111"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0010000"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0010001"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][3]];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0010010"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0010011"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante[formato[i][3]];
        }
        else if (linea == "0010100"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }

        // OR

        else if (linea == "0010101"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0010110"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0010111"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0011000"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][3]];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0011001"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0011010"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante[formato[i][3]];
        }
        else if (linea == "0011011"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }

        // MUL

        else if (linea == "0011100"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0011101"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0011110"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0011111"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][3]];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0100000"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0100001"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante[formato[i][3]];
        }
        else if (linea == "0100010"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }

        // DIV

        else if (linea == "0100011"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0100100"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0100101"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0100110"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][3]];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0100111"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0101000"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante[formato[i][3]];
        }
        else if (linea == "0101001"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }


        // MOV

        else if (linea == "0101010"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0101011"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0101100"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0101101"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][3]];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0101110"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        else if (linea == "0101111"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante[formato[i][3]];
        }
        else if (linea == "0110000"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }

        // BRM
        else if (linea == "0110001"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        // BRI
        else if (linea == "0110010"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        // BRME
        else if (linea == "0110011"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante["0"];
        }
        // SHL
        else if (linea == "0110100"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante[formato[i][3]];
        }
        // SHR
        else if (linea == "0110101"){
            linea += registros[formato[i][1]];
            linea += registros[formato[i][2]];
            linea += constante[formato[i][3]];
        }
        // NOP
        else if (linea == "0110110"){
            linea += registros["R1"];
            linea += registros["R1"];
            linea += constante["0"];
        }
        // JUMP
        else if (linea == "0110111"){
            linea += registros["R1"];
            linea += registros["R1"];
            linea += constante["0"];
        }

        // segundos ADD
        else if (linea == "0111000"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0111001"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0111010"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }
        else if (linea == "0111011"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }

        // segundos SUB
        else if (linea == "0111100"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0111101"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "0111110"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }
        else if (linea == "0111111"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }

        // segundos AND
        else if (linea == "1000000"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "1000001"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "1000010"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }
        else if (linea == "1000011"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }

        // segundos OR
        else if (linea == "1000100"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "1000101"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "1000110"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }
        else if (linea == "1000111"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }

        // segundos MUL
        else if (linea == "1001000"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "1001001"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "1001010"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }
        else if (linea == "1001011"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }

        // segundos DIV
        else if (linea == "1001100"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "1001101"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "1001110"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }
        else if (linea == "1001111"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }

        // segundos MOV
        else if (linea == "1010000"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "1010001"){
            linea += registros[formato[i][1]];
            linea += registros["R1"];
            linea += constante[formato[i][2]];
        }
        else if (linea == "1010010"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }
        else if (linea == "1010011"){
            linea += registros[formato[i][2]];
            linea += registros["R1"];
            linea += constante[formato[i][1]];
        }


        // ultimo MOV
        else if (linea == "1010100"){
            linea += registros[formato[i][1]];
            linea += constante[formato[i][2]];
            linea += registros[formato[i][3]];
        }
        // ultimo ADD
        else if (linea == "1010101"){
            linea += registros[formato[i][1]];
            linea += constante[formato[i][2]];
            linea += registros[formato[i][3]];
        }
        // ultimo SUB
        else if (linea == "1010110"){
            linea += registros[formato[i][1]];
            linea += constante[formato[i][2]];
            linea += registros[formato[i][3]];
        }
        // ultimo MUL
        else if (linea == "1010111"){
            linea += registros[formato[i][1]];
            linea += constante[formato[i][2]];
            linea += registros[formato[i][3]];
        }
        // ultimo DIV
        else if (linea == "1011000"){
            linea += registros[formato[i][1]];
            linea += constante[formato[i][2]];
            linea += registros[formato[i][3]];
        }
        // ultimo AND
        else if (linea == "1011001"){
            linea += registros[formato[i][1]];
            linea += constante[formato[i][2]];
            linea += registros[formato[i][3]];
        }
        // ultimo OR
        else if (linea == "1011010"){
            linea += registros[formato[i][1]];
            linea += constante[formato[i][2]];
            linea += registros[formato[i][3]];
        }
        /* En caso de que la informacion no sea reconocida */
        else
        {
            linea = "XXXXXXXXXXXXXXXX";
        }
        linea += "\n";
        text_out += linea;
    }

    QString qdisp = QString::fromStdString(text_out);
    return qdisp;


}

void Assembler::on_pushButton_clicked()
{
    QString texto;

    texto = ui->textEdit->toPlainText();
    QString text_disp = translate(texto.toUpper());
    ui->textBrowser->append(text_disp);
}

void Assembler::on_pushButton_2_clicked()
{
    QFile mFile ("C:\\Users\\Mario\\Documents\\Assembler\\instrucciones.txt");
    if(!mFile.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"title","file not open");
    }
    QTextStream in(&mFile);
    QString text = in.readAll();

    qDebug() << text;
    ui->textBrowser->append(translate(text.toUpper()));
    ui->textEdit->setText(text);

}

void Assembler::on_textEdit_selectionChanged()
{

}
