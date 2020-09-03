#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// wheel settings for the Lorenz cipher
char chi1[41] = {1,1,1,1,1,0,0,0,1,0,1,0,1,1,0,0,0,1,1,1,1,0,0,0,1,0,1,1,1,0,1,0,0,0,1,0,0,0,1,1,1};
char chi2[31] = {1,1,0,0,0,0,1,1,0,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,0,1,0,0,0};
char chi3[29] = {1,0,0,0,1,0,0,1,1,1,1,0,0,1,1,0,0,0,1,1,1,0,1,1,1,1,0,1,0};
char chi4[26] = {1,1,1,1,0,0,0,1,1,0,1,0,0,0,1,0,0,0,1,1,1,0,1,0,0,1};
char chi5[23] = {1,1,0,1,1,1,1,0,0,0,0,0,0,1,0,1,0,0,0,1,1,1,0};

char psi1[43] = {1,0,1,1,0,0,0,1,1,0,1,0,0,1,0,1,0,0,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,0};
char psi2[47] = {1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,0,0,1,0,1,0,1,0,1,0,1,1,1,0};
char psi3[51] = {1,0,1,0,0,0,0,1,0,0,1,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,1};
char psi4[53] = {0,1,0,1,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,1,1,0,1,1,0,1,0,1,0,0,1,1,0,1,1,0,1,0,1,1,0,1,0,1,1,0,0,1};
char psi5[59] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,0,1,0,0,1,1,0,1,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,0,1,0};

char mu1[61] = {0,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,1,0,0,1,0,0,0,1,1,1,0,1,1,1,1,0,0,0,1,0,0,1,0,0,1,1,1,0,0,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,0};
char mu2[37] = {0,1,1,1,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,1,1,1,1,1,1,1,1,1};

//data for baudot translation
char alphabet[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char alphabetSimple[27]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char figures[25] = {'0','1','2','3','4','5','6','7','8','9','-',',','!',':','(','+',')','$','?','&','.','/','=','\''};
char alphabetBaudot[25][5]= {{0,0,0,1,1},{1,1,0,0,1},{0,1,1,1,0},{0,1,0,0,1},{0,0,0,0,1},{0,1,1,0,1},{1,1,0,1,0},{1,0,1,0,0},{0,0,1,1,0},{0,1,0,1,1},{0,1,1,1,1},{1,0,0,1,0},{1,1,1,0,0},{0,1,1,0,0},{1,1,0,0,0},{1,0,1,1,0},{1,0,1,1,1},{0,1,0,1,0},{0,0,1,0,1},{1,0,0,0,0},{0,0,1,1,1},{1,1,1,1,0},{1,0,0,1,1},{1,1,1,0,1},{1,0,1,0,1},{1,0,0,0,1}};
char figuresBaudot[24][6]={{1,0,1,1,0},{1,0,1,1,1},{1,0,0,1,1},{0,0,0,0,1},{0,1,0,1,0},{1,0,0,0,0},{1,0,1,0,1},{0,0,1,1,1},{0,0,1,1,0},{1,1,0,0,0},{0,0,0,1,1},{0,1,1,0,0},{0,1,1,0,1},{0,1,1,1,0},{0,1,1,1,1},{1,0,0,0,1},{1,0,0,1,0},{1,0,1,0,0},{1,1,0,0,1},{1,1,0,1,0},{1,1,1,0,0},{1,1,1,0,1},{1,1,1,1,0},{0,0,1,0,1}};
char space[5]={0,0,1,0,0};
char changeletters[5]={1,1,1,1,1};
char changefigures[5]={1,1,0,1,1};

int y=0; // a counter for adding 0/1 to baudotText array

//Wikipedia text source - https://en.wikipedia.org/wiki/Teleprinter
char plaintext[]="The teleprinter evolved through a series of inventions by a number of engineers, including Samuel Morse, Alexander Bain, Royal Earl House, David Edward Hughes, Emile Baudot, Donald Murray, Charles L. Krum, Edward Kleinschmidt and Frederick G. Creed. Teleprinters were invented in order to send and receive messages without the need for operators trained in the use of Morse code. A system of two teleprinters, with one operator trained to use a keyboard, replaced two trained Morse code operators. The teleprinter system improved message speed and delivery time, making it possible for messages to be flashed across a country with little manual intervention. There were a number of parallel developments on both sides of the Atlantic Ocean. In 1835 Samuel Morse devised a recording telegraph, and Morse code was born. Morse's instrument used a current to displace the armature of an electromagnet, which moved a marker, therefore recording the breaks in the current. Cooke  Wheatstone received a British patent covering telegraphy in 1837 and a second one in 1840 which described a type-printing telegraph with steel type fixed at the tips of petals of a rotating brass daisy-wheel, struck by an electric hammer to print Roman letters through carbon paper onto a moving paper tape. In 1841 Alexander Bain devised an electromagnetic printing telegraph machine. It used pulses of electricity created by rotating a dial over contact points to release and stop a type-wheel turned by weight-driven clockwork; a second clockwork mechanism rotated a drum covered with a sheet of paper and moved it slowly upwards so that the type-wheel printed its signals in a spiral. The critical issue was to have the sending and receiving elements working synchronously. Bain attempted to achieve this using centrifugal governors to closely regulate the speed of the clockwork. It was patented, along with other devices, on April 21, 1841. By 1846, the Morse telegraph service was operational between Washington, D.C., and New York. Royal Earl House patented his printing telegraph that same year. He linked two 28-key piano-style keyboards by wire. Each piano key represented a letter of the alphabet and when pressed caused the corresponding letter to print at the receiving end. A 'shift' key gave each main key two optional values. A 56-character typewheel at the sending end was synchronised to coincide with a similar wheel at the receiving end. If the key corresponding to a particular character was pressed at the home station, it actuated the typewheel at the distant station just as the same character moved into the printing position, in a way similar to the daisy wheel printer. It was thus an example of a synchronous data transmission system. House's equipment could transmit around 40 instantly readable words per minute, but was difficult to manufacture in bulk. The printer could copy and print out up to 2,000 words per hour. This invention was first put in operation and exhibited at the Mechanics Institute in New York in 1844. Landline teleprinter operations began in 1849, when a circuit was put in service between Philadelphia and New York City.[6] In 1855, David Edward Hughes introduced an improved machine built on the work of Royal Earl House. In less than two years, a number of small telegraph companies, including Western Union in early stages of development, united to form one large corporation – Western Union Telegraph Co. – to carry on the business of telegraphy on the Hughes system. In France, Emile Baudot designed in 1874 a system using a five-unit code, which began to be used extensively in that country from 1877. The British Post Office adopted the Baudot system for use on a simplex circuit between London and Paris in 1897, and subsequently made considerable use of duplex Baudot systems on their Inland Telegraph Services. During 1901, Baudot's code was modified by Donald Murray (1865–1945, originally from New Zealand), prompted by his development of a typewriter-like keyboard. The Murray system employed an intermediate step, a keyboard perforator, which allowed an operator to punch a paper tape, and a tape transmitter for sending the message from the punched tape. At the receiving end of the line, a printing mechanism would print on a paper tape, and/or a reperforator could be used to make a perforated copy of the message. As there was no longer a direct correlation between the operator's hand movement and the bits transmitted, there was no concern about arranging the code to minimize operator fatigue, and instead Murray designed the code to minimize wear on the machinery, assigning the code combinations with the fewest punched holes to the most frequently used characters. The Murray code also introduced what became known as 'format effectors' or 'control characters' – the CR (Carriage Return) and LF (Line Feed) codes. A few of Baudot's codes moved to the positions where they have stayed ever since: the NULL or BLANK and the DEL code. NULL/BLANK was used as an idle code for when no messages were being sent. In the United States in 1902, electrical engineer Frank Pearne approached Joy Morton, head of Morton Salt, seeking a sponsor for research into the practicalities of developing a printing telegraph system. Joy Morton needed to determine whether this was worthwhile and so consulted mechanical engineer Charles L. Krum, who was vice president of the Western Cold Storage Company. Krum was interested in helping Pearne, so space was set up in a laboratory in the attic of Western Cold Storage.";

//convert a plain text to baudot
void convert_baudot(char text[],char baudotText[]){
    int status = 0; // status 0 for letters status -1 for figures
    for(int i=0; i<strlen(text); i++){
        for(int j=0; j<strlen(alphabet); j++){
            if(text[i]==' '){
                for(int x=0;x<5;x++){
                    baudotText[y]=space[x];
                    y++;
                }
                break;
            }
            if(text[i]==alphabet[j] || text[i]==alphabetSimple[j]){
                if(status == 1){
                    for(int x=0;x<5;x++){
                        baudotText[y]=changeletters[x];
                        y++;
                    }
                }
                status = 0;
                for(int x=0;x<5;x++){
                    baudotText[y]=alphabetBaudot[j][x];
                    y++;
                }
                break;
            }
        }
        for(int k=0; k<strlen(figures); k++){
            if(text[i]==figures[k]){
                if(status == 0){
                    for(int x=0;x<5;x++){
                        baudotText[y]=changefigures[x];
                        y++;
                    }
                }
                status = 1;
                for(int x=0;x<5;x++){
                    baudotText[y]=figuresBaudot[k][x];
                    y++;
                }
                break;
            }
        }
    }
}

// get the number of bits from the input plaintext that was changed in the ciphertext as a percentage.
void count_percentage(char arr1[],char arr2[],int len){
    int count=0;
    for(int i=0;i<len;i++){
        if (arr1[i]!= arr2[i]){
            count++;
        }
    }
    double pecentage = count*100.0/y;
    printf("%f",pecentage);
}

// wheel rotation (shift register operation)
void move_chi_pos(int chi_pos[5]){
    chi_pos[0] = (chi_pos[0] + 1) % 41;
    chi_pos[1] = (chi_pos[1] + 1) % 31;
    chi_pos[2] = (chi_pos[2] + 1) % 29;
    chi_pos[3] = (chi_pos[3] + 1) % 26;
    chi_pos[4] = (chi_pos[4] + 1) % 23;
}
void move_psi_pos(int psi_pos[5]){
    psi_pos[0] = (psi_pos[0] + 1) % 43;
    psi_pos[1] = (psi_pos[1] + 1) % 47;
    psi_pos[2] = (psi_pos[2] + 1) % 51;
    psi_pos[3] = (psi_pos[3] + 1) % 53;
    psi_pos[4] = (psi_pos[4] + 1) % 59;
}
void move_mu_pos1(int *mu_pos1){
    *mu_pos1 = (*mu_pos1 + 1) % 61;
}
void move_mu_pos2(int *mu_pos2){
    *mu_pos2 = (*mu_pos2 + 1) % 37;
}


void main(void) {
    char baudotText[100000];
    char chipherText[100000];
    char lorenzkeys[100000];
    printf("Wikipedia source - https://en.wikipedia.org/wiki/Teleprinter\n\nExtracted text from the topic 'History'-\n");
    //print a portion of the plain text
    for(int i=0; i<79; i++){
        printf("%c",plaintext[i]);
    }
    printf(" ... (to be continued)\n");
    printf("\n=================================================================================================\n");

    convert_baudot(plaintext,baudotText);

    //print the baudot code
    printf("\nCorresponding Baudot codes (first twenty codes only) -\n");
    for(int i=0; i<100; i++){
        if(i%5==0)
            printf(" ");
        printf("%i",baudotText[i]);
    }
    printf("\n=================================================================================================\n");

    char K[5];
    char clock_mu_wheel;
    char clock_psi_wheel;
    // Starting positions of wheels
    int chi_pos[5] = {0,0,0,0,0};
    int psi_pos[5] = {0,0,0,0,0};
    int mu_pos[2] = {0,0};

    for(int t=0; t<(y/5); t++) {
        // 1. Encrypting each 5-bit word at time t
        // K_t = chi_t^i \xor psi_{t_chi}^i
        K[0] = chi1[chi_pos[0]] ^ psi1[psi_pos[0]];
        K[1] = chi2[chi_pos[1]] ^ psi2[psi_pos[1]];
        K[2] = chi3[chi_pos[2]] ^ psi3[psi_pos[2]];
        K[3] = chi4[chi_pos[3]] ^ psi4[psi_pos[3]];
        K[4] = chi5[chi_pos[4]] ^ psi5[psi_pos[4]];
        for(int z=0;z<5;z++){
            lorenzkeys[t*5+z]=K[z];
        }

        clock_mu_wheel = 0;
        clock_psi_wheel = 0;
        // 2. clock ticked as t = t+1
        // move all chi wheels
        move_chi_pos(chi_pos);
        // move first mu wheel
        move_mu_pos1(&mu_pos[0]);
        // 3. check for mu wheel rotation
        if(mu1[mu_pos[0]] == 1)
            clock_mu_wheel = 1;
        // move mu wheels
        if(clock_mu_wheel == 1) {
            move_mu_pos2(&mu_pos[1]);
        }
        // 4. check for psi wheel rotation
        if(mu2[mu_pos[1]] == 1)
            clock_psi_wheel = 1;
        // move psi wheels
        if(clock_psi_wheel == 1)
            move_psi_pos(psi_pos);
    }

    printf("\nLorenz cipher key streams (first twenty key streams only) -\n");
    for(int i=0; i<100; i++){
        if(i%5==0)
            printf(" ");
        printf("%i",lorenzkeys[i]);
    }

    //get the cipher text by XOR the baudot code and lorenz key stream
    for(int i=0; i<y; i++){
        chipherText[i]=baudotText[i]^lorenzkeys[i];
    }
    printf("\n=================================================================================================\n");

    printf("\nCorresponding chiper codes (first twenty cipher codes only) -\n");
    for(int i=0; i<100; i++){
        if(i%5==0)
            printf(" ");
        printf("%i",chipherText[i]);
    }
    printf("\n=================================================================================================\n");

    printf("\nThe percentage of the changed bits (full text) = ");
    count_percentage(baudotText,chipherText,y);
    printf("%c",'%');
    printf("\n");
}


