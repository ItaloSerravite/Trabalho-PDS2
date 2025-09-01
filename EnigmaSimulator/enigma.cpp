#include <iostream>
#include <cctype>
#include <vector>
using namespace std;

//A B C D E F G H I J K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
struct Rotor{

	const int disposicao[5][26] ={
		//EKMF LGDQ VZNT OWYH XUSP AIBR CJ
		{4,10,12,5,11,6,3,16,21,25,13,19,14,22,24,7,23,20,18,15,0,8,1,17,2,9},
		//AJDK SIRU XBLH WTMC QGZN PYFV OE
		{0,9,3,10,18,8,17,20,23,1,11,7,22,19,12,2,16,6,25,13,15,24,5,21,14,4},
		//BDFH JLCP RTXV ZNYE IWGA KMUS QO
		{1,3,5,7,9,11,2,15,17,19,23,21,25,13,24,4,8,22,6,0,10,12,20,18,16,14},
		//ESOV PZJA YQUI RHXL NFTG KDCM WB
		{4,18,14,21,15,25,9,0,24,16,20,8,17,7,23,11,13,5,19,6,10,3,2,12,22,1},
		//VZBR GITY UPSD NHLX AWMJ QOFE CK
		{21,25,1,17,6,8,19,24,20,15,18,3,13,7,11,23,0,22,12,9,16,14,5,4,2,10}
	};

	const int disposicao_inversa[5][26] ={                            
		{20,22,24,6,0,3,5,15,21,25,1,4,2,10,12,19,7,23,18,11,17,8,13,16,14,9}, 
		{0,9,15,2,25,22,17,11,5,1,3,10,14,19,24,20,16,6,4,13,7,23,12,8,21,18}, 
		{19,0,6,1,15,2,18,3,16,4,20,5,21,13,25,7,24,8,23,9,22,11,17,10,14,12},
		{7,25,22,21,0,17,19,13,11,6,20,15,23,16,2,4,9,12,1,18,10,3,24,14,8,5},
		{16,2,24,11,23,22,4,13,20,19,25,14,18,12,21,9,10,3,6,8,0,17,15,7,1}
	};
	
	const int disposicao_refletor[2][26] = {
		//AY BR CU DH EQ FS GL IP JX KN MO TZ VW
		{24,17,20,7,16,18,11,3,15,23,13,6,14,10,12,8,4,1,5,25,2,22,21,9,0,19},
		//AF BV CP DJ EI GO HY KR LZ MX NW QT SU
		{5,21,15,9,8,0,14,24,4,3,17,25,23,22,6,2,19,10,20,16,18,1,13,12,7,11}
	};
	//posicao do rotor imediatamente a direita na janela antes de rotacionar os rotores da esquerda e do meio
	//Q E V J Z
	const int janela[5] = {16,4,21,9,25};

	//numero do rotor que ficara em cada posicao
	int rotor_direito;
	int rotor_esquerdo;
	int rotor_meio;
	
	int posicao_atual_direito;
	int posicao_atual_meio;
	int posicao_atual_esquerdo;

	int refletor_escolhido;

	//posicoes e tipos de rotores escolhidos
	void rodar(){


		if(posicao_atual_meio==janela[rotor_meio]){
            posicao_atual_esquerdo = (posicao_atual_esquerdo+1)%26;
			posicao_atual_meio = (posicao_atual_meio+1)%26;
			posicao_atual_direito = (posicao_atual_direito+1)%26;
			return;
		}
		if(posicao_atual_direito == janela[rotor_direito])
			posicao_atual_meio = (posicao_atual_meio+1)%26;
		posicao_atual_direito = (posicao_atual_direito+1)%26;
	}

};

struct Painel{
	int posicoes[26] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
};

char codifica(Rotor *rotor, Painel *painel, char letra_atual){

	int num_letra = tolower(letra_atual) - 97;
	
	int troca_1 = painel->posicoes[num_letra];
	int troca_2 = (rotor->disposicao[rotor->rotor_direito][(troca_1+rotor->posicao_atual_direito)%26]+26-rotor->posicao_atual_direito)%26;
	int troca_3 = (rotor->disposicao[rotor->rotor_meio][(troca_2+rotor->posicao_atual_meio)%26]+26-rotor->posicao_atual_meio)%26;
	int troca_4 = (rotor->disposicao[rotor->rotor_esquerdo][(troca_3+rotor->posicao_atual_esquerdo)%26]+26-rotor->posicao_atual_esquerdo)%26;
	int troca_5 = rotor->disposicao_refletor[rotor->refletor_escolhido][troca_4];
	int troca_6 = (rotor->disposicao_inversa[rotor->rotor_esquerdo][(troca_5+rotor->posicao_atual_esquerdo)%26]+26-rotor->posicao_atual_esquerdo)%26;
	int troca_7 = (rotor->disposicao_inversa[rotor->rotor_meio][(troca_6+rotor->posicao_atual_meio)%26]+26-rotor->posicao_atual_meio)%26;
	int troca_8 = (rotor->disposicao_inversa[rotor->rotor_direito][(troca_7+rotor->posicao_atual_direito)%26]+26-rotor->posicao_atual_direito)%26;
	int troca_9 = painel->posicoes[troca_8];

	troca_9 += 97;
	return (char) troca_9;
}


int main(){

	Rotor *rotor = new Rotor;
	cout << "Digite quais rotores ira utilizar da esquerda para a direita: ";
	cin >> rotor->rotor_esquerdo >> rotor->rotor_meio >> rotor->rotor_direito;
	rotor->rotor_esquerdo--;
	rotor->rotor_meio--;
	rotor->rotor_direito--;

	cout << "Digite a posicao de cada rotor(letra que aparecera no visor) da esquerda para a direita: ";
	char a, b, c;
	cin >> a >> b >> c;
	rotor->posicao_atual_esquerdo = (int) tolower(a) - 97;
	rotor->posicao_atual_meio = (int) tolower(b) - 97;
	rotor->posicao_atual_direito =  (int) tolower(c) - 97;

	char tipo_refletor;
	cout << "Digite qual refletor ira utilizar(B ou C): ";
	cin >> tipo_refletor;
	char lower_tipo = tolower(tipo_refletor);
	if(lower_tipo == 'b')
		rotor->refletor_escolhido = 0;
	else rotor->refletor_escolhido = 1;

	Painel *painel = new Painel;
	int plugins;
	cout << "Quantos pares de letras ira plugar no painel(0 a 10): ";
	cin >> plugins;
	cout << "Digite os pares(letra por letra): ";
	for(int i = 0; i < plugins; i++){
		char a, b; 
		cin >> a >> b;
		int x = tolower(a) - 97, y =  tolower(b) - 97;
		painel->posicoes[x] = y;
		painel->posicoes[y] = x;
	}

	vector<char> output;
	cout << "Digite o texto a ser criptografado(asterisco ao final): ";
	char letra;
	cin >> letra;
	letra = tolower(letra);
	while(letra != '*'){

		if(letra == ' '){
			output.push_back(' ');
			cin >> letra;
			letra = tolower(letra);
			continue;
		}
		//roda antes de codificar
		rotor->rodar();
		char letra_codificada = codifica(rotor,painel,letra);
		output.push_back(letra_codificada);

		cin >> letra;
		letra = tolower(letra);

	}

	for(auto x : output){
		cout << x;
	}

	delete rotor;
	delete painel;

	return 0;
}