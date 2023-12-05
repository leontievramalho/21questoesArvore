#include <iostream>
#include <string>
using namespace std;

struct NoArvore{
	int fb;
	int key;
	NoArvore *esquerda;
	NoArvore *direita;
};

struct NoArvoreNaria{
	int key;
	NoArvoreNaria *primeiroFilho;
	NoArvoreNaria *proxIrmao;
};

void exibirArvoreOrdem(NoArvore *raiz){
	if(raiz != NULL){
		exibirArvoreOrdem(raiz -> esquerda);
		cout << raiz -> key << " ";
		exibirArvoreOrdem(raiz -> direita);
	}
}

void exibirArvoreOrdemFb(NoArvore *raiz){
	if(raiz != NULL){
		exibirArvoreOrdemFb(raiz -> esquerda);
		cout << "Key = " << raiz -> key << " FB = " << raiz -> fb << ", ";
		exibirArvoreOrdemFb(raiz -> direita);
	}
}

void exibirArvorePreOrdem(NoArvore *raiz){
	if(raiz != NULL){
		cout << raiz -> key << " ";
		exibirArvorePreOrdem(raiz -> esquerda);
		exibirArvorePreOrdem(raiz -> direita);
	}
}

void exibirArvorePosOrdem(NoArvore *raiz){
	if(raiz != NULL){
		exibirArvorePosOrdem(raiz -> esquerda);
		exibirArvorePosOrdem(raiz -> direita);
		cout << raiz -> key << " ";
	}
}

void posOrdemNaria(NoArvoreNaria *raiz){
	if(raiz != NULL){
		posOrdemNaria(raiz->primeiroFilho);
		posOrdemNaria(raiz->proxIrmao);
		cout << raiz -> key << " ";
	}
}

bool sameBST(NoArvore *raiz1, NoArvore *raiz2){
	if(raiz1==NULL){
		if(raiz2!=NULL){
			return false;
		}
		return true;
	}
	if(raiz1 -> key == raiz2 -> key){
		return sameBST(raiz1 -> esquerda, raiz2 -> esquerda) && sameBST(raiz1 -> direita, raiz2 -> direita);
	}
	return false;
}

int heightArvore(NoArvore *raiz){
	if(raiz == NULL){
		return 0;
	}else{
		if(raiz -> esquerda == NULL && raiz -> direita == NULL){
			return 1;
		}else if(raiz -> esquerda != NULL && raiz -> direita != NULL){
			if(heightArvore(raiz -> direita) >= heightArvore(raiz -> esquerda)){
				return 1 + heightArvore(raiz -> direita);
			}else{
				return 1 + heightArvore(raiz -> esquerda);
			}
		}else if(raiz -> esquerda != NULL){
			return 1 + heightArvore(raiz -> esquerda);
		}else{
			return 1 + heightArvore(raiz -> direita);
		}
	}
}

int alturaArvore(NoArvore *raiz){
	if(raiz == NULL){
		return 0;
	}else{
		if(raiz -> esquerda == NULL && raiz -> direita == NULL){
			return 0;
		}else if(raiz -> esquerda != NULL && raiz -> direita != NULL){
			if(alturaArvore(raiz -> direita) >= alturaArvore(raiz -> esquerda)){
				return 1 + alturaArvore(raiz -> direita);
			}else{
				return 1 + alturaArvore(raiz -> esquerda);
			}
		}else if(raiz -> esquerda != NULL){
			return 1 + alturaArvore(raiz -> esquerda);
		}else{
			return 1 + alturaArvore(raiz -> direita);
		}
	}
}

NoArvore *rotacaoDireita(NoArvore *&raiz){
	if(raiz != NULL && raiz -> esquerda != NULL){
		NoArvore *aux = raiz;
		raiz = raiz -> esquerda;
		aux -> esquerda = NULL;
		if(raiz -> direita != NULL){
			aux -> esquerda = raiz -> direita;
		}
		raiz -> direita = aux;
	}
	return raiz;
}

NoArvore *rotacaoEsquerda(NoArvore *&raiz){
	if(raiz != NULL && raiz -> direita != NULL){
		NoArvore *aux = raiz;
		raiz = raiz -> direita;
		aux -> direita = NULL;
		if(raiz -> esquerda != NULL){
			aux -> direita = raiz -> esquerda;
		}
		raiz -> esquerda = aux;	
	}
	return raiz;
}

NoArvore *rotacaoDuplaDireita(NoArvore *&raiz){
	if(raiz != NULL && raiz -> esquerda != NULL){
		rotacaoEsquerda(raiz -> esquerda);
		return rotacaoDireita(raiz);
	}
}

NoArvore *rotacaoDuplaEsquerda(NoArvore *&raiz){
	if(raiz != NULL && raiz -> direita != NULL){
		rotacaoDireita(raiz -> direita);
		return rotacaoEsquerda(raiz);
	}
}

void atualizarFb(NoArvore *&raiz){
	if(raiz != NULL){
		raiz -> fb = heightArvore(raiz -> esquerda) - heightArvore(raiz -> direita);
		atualizarFb(raiz -> esquerda);
		atualizarFb(raiz -> direita);
	}
}

NoArvore *balancearAVL(NoArvore *&raiz){
	if(raiz != NULL){
		balancearAVL(raiz -> esquerda);
		balancearAVL(raiz -> direita);
		atualizarFb(raiz);
		if(raiz -> fb > 1){
			if(raiz -> esquerda -> fb >= 0){
				return rotacaoDireita(raiz);
			}else{
				return rotacaoDuplaDireita(raiz);
			}
		}else if(raiz -> fb < -1){
			if(raiz -> direita -> fb <= 0){
				return rotacaoEsquerda(raiz);
			}else{
				return rotacaoDuplaEsquerda(raiz);
			}
		}
		return raiz;
	}
}

NoArvore *inserirSemFb(NoArvore *&raiz, int chave){
	if(raiz == NULL){
		NoArvore *novoNo = new NoArvore;
		novoNo -> key = chave;
		novoNo -> esquerda = NULL;
		novoNo -> direita = NULL;
		novoNo -> fb = 0;
		raiz = novoNo;
		return raiz;
	} else if(chave < raiz -> key){
		return inserirSemFb(raiz->esquerda, chave);
	} else if(chave > raiz -> key){
		return inserirSemFb(raiz->direita, chave);
	}else{
		cout << "Chave ja existe." << endl;
	}
}

NoArvore *inserirTrioSemFb(NoArvore *&raiz, int chave){
	if(raiz == NULL){
		NoArvore *novoNo = new NoArvore;
		novoNo -> key = chave;
		novoNo -> esquerda = NULL;
		novoNo -> direita = NULL;
		novoNo -> fb = 0;
		raiz = novoNo;
		return raiz;
	} else if(raiz -> esquerda == NULL){
		return inserirTrioSemFb(raiz -> esquerda, chave);
	} else if(raiz -> direita == NULL){
		return inserirTrioSemFb(raiz -> direita, chave);
	}else{
		cout << "A arvore ja possui raiz e 2 filhos." << endl;
	}
}

NoArvore *inserirAVL(NoArvore *&raiz, int chave){
	inserirSemFb(raiz, chave);
	raiz = balancearAVL(raiz);
	atualizarFb(raiz);
	return raiz;
}

NoArvore *inserir(NoArvore *&raiz, int chave){
	inserirSemFb(raiz, chave);
	atualizarFb(raiz);
	return raiz;
}

NoArvore *inserirTrio(NoArvore *&raiz, int chave){
	inserirTrioSemFb(raiz, chave);
	atualizarFb(raiz);
	return raiz;
}

bool isBalanced(NoArvore *raiz){
	atualizarFb(raiz);
	if(raiz != NULL){
		return (raiz -> fb < 2 && raiz -> fb > -2) && isBalanced(raiz -> esquerda) && isBalanced(raiz -> direita);
	}else{
		return true;
	}
}

void balancearArvore(NoArvore *&raiz){
	while(isBalanced(raiz) != true){
		raiz = balancearAVL(raiz);
		atualizarFb(raiz);
	}
}

bool isBST(NoArvore *raiz){
	if(raiz != NULL){
		if(raiz -> esquerda == NULL && raiz -> direita == NULL){
			return true;
		}else if(raiz -> direita == NULL){
			if(raiz -> esquerda -> key >= raiz -> key){
				return false;
			}
			return isBST(raiz-> esquerda);
		}else if(raiz -> esquerda == NULL){
			if(raiz -> direita -> key <= raiz -> key){
				return false;
			}
			return isBST(raiz-> direita);
		}else{
			if(raiz -> direita -> key <= raiz -> key || raiz -> esquerda -> key >= raiz -> key){
				return false;
			}
			return isBST(raiz->esquerda) && isBST(raiz -> direita);
		}
	}else{
		return true;
	}
}

void inverterArvore(NoArvore *&raiz){
	if(raiz != NULL){
		NoArvore *aux = raiz -> esquerda;
		raiz -> esquerda = raiz -> direita;
		raiz -> direita = aux;
		inverterArvore(raiz -> esquerda);
		inverterArvore(raiz -> direita);
	}
}

NoArvore *mergeArvore(NoArvore *raiz1, NoArvore *raiz2){
	NoArvore *novaRaiz = new NoArvore;
	novaRaiz -> esquerda = NULL;
	novaRaiz -> direita = NULL;
	novaRaiz -> fb = 0;
	if(raiz1 != NULL && raiz2 != NULL){
		novaRaiz -> key = raiz1 -> key + raiz2 -> key;
		novaRaiz -> esquerda = mergeArvore(raiz1 -> esquerda, raiz2 -> esquerda);
		novaRaiz -> direita = mergeArvore(raiz1 -> direita, raiz2 -> direita);
		atualizarFb(novaRaiz);
		return novaRaiz;
	} else if(raiz1 != NULL){
		novaRaiz = raiz1;
	} else if(raiz2 != NULL){
		novaRaiz = raiz2;
	} else{
		delete novaRaiz;
		return NULL;
	}
}

int contarNo(NoArvore *raiz){
	if(raiz!=NULL){
		return 1 + contarNo(raiz -> esquerda) + contarNo(raiz -> direita);
	}else{
		return 0;
	}
}

bool somaIgualRaiz(NoArvore *raiz){
	if(contarNo(raiz) == 3 && raiz -> esquerda != NULL && raiz -> direita != NULL){
		return (raiz -> key == raiz -> esquerda -> key + raiz -> direita -> key);
	} else{
		cout << "A arvore nao possui exatos 3 elementos (raiz, filho esquerda e filho direita)." << endl;
	}
}

int somaFolhas(NoArvore *raiz){
	if(raiz!=NULL){
		if(raiz->esquerda==NULL && raiz->direita == NULL){
			return raiz -> key;
		}else{
			return somaFolhas(raiz -> esquerda) + somaFolhas(raiz -> direita);
		}
	}else{
		return 0;
	}
}

NoArvore *maiorNo(NoArvore *no1, NoArvore *no2){
	if(no1 != NULL && no2 != NULL){
		if(no1 -> key > no2 -> key){
			return no1;
		}else{
			return no2;
		}
	}else if(no1 == NULL){
		return no2;
	} else if(no2 == NULL){
		return no1;
	} else{
		return NULL;
	}	
}

NoArvore *maiorNivel(NoArvore *raiz, int nivel){
	if(raiz != NULL){
		if(nivel == 0){
			return raiz;
		}else if(nivel == 1){
			return maiorNo(raiz -> esquerda, raiz -> direita);
		}else{
			return maiorNo(maiorNivel(raiz -> esquerda, nivel-1), maiorNivel(raiz -> direita, nivel-1));
		}
	}else{
		return NULL;
	}
}

void maiorCadaNivel(NoArvore *raiz){
	for(int i = 0; i < heightArvore(raiz); i++){
		cout << "Maior do nivel " << i << ": " << maiorNivel(raiz, i) -> key << endl;
	}
}

int somaNos(NoArvore *raiz){
	if(raiz!=NULL){
		return raiz -> key + somaNos(raiz -> esquerda) + somaNos(raiz -> direita);
	}else{
		return 0;
	}
}

int somaMaiorSubarvore(NoArvore *raiz){
	int somaEsquerda = somaNos(raiz -> esquerda);
	int somaDireita = somaNos(raiz -> direita);
	if(somaEsquerda > somaDireita){
		return somaEsquerda;
	}else{
		return somaDireita;
	}
}

NoArvore *arrayParaArvore(int vetor[], int tamanhoVetor){
	NoArvore *raiz = NULL;
	for(int i = 0; i<tamanhoVetor; i++){
		inserir(raiz, vetor[i]);
	}
	return raiz;
}

NoArvore *maiorBST(NoArvore *raiz){
	if(raiz != NULL && raiz -> direita == NULL){
		return raiz;
	}else if(raiz != NULL && raiz -> direita != NULL){
		return maiorBST(raiz->direita);
	}
}

NoArvore *menorBST(NoArvore *raiz){
	if(raiz != NULL && raiz -> esquerda == NULL){
		return raiz;
	}else if(raiz != NULL && raiz -> esquerda != NULL){
		return menorBST(raiz->esquerda);
	}
}

NoArvore *buscaBinaria(NoArvore *raiz, int valor){
	if(raiz==NULL || raiz->key == valor){
		return raiz;
	}else if(valor < raiz -> key){
		buscaBinaria(raiz->esquerda, valor);
	} else{
		buscaBinaria(raiz->direita, valor);
	}
}

void resultadoBuscaBinaria(NoArvore *raiz, int valor){
	NoArvore *resultado = buscaBinaria(raiz, valor);
	if(resultado == NULL){
		cout << valor << " nao encontrado na arvore." << endl;
	}else{
		cout << valor << " encontrado. Key = " << resultado -> key <<endl;
	}
}
/*
string printCaminho(NoArvore *raiz){
	if(raiz != NULL){
		if(raiz -> esquerda == NULL && raiz -> direita == NULL){
			return to_string(raiz -> key) + ", ";
		} else if(raiz -> direita == NULL){
			return to_string(raiz -> key) + "->" + printCaminho(raiz -> esquerda);
		} else if(raiz -> esquerda == NULL){
			return to_string(raiz -> key) + "->" + printCaminho(raiz -> direita);
		} else{
			return to_string(raiz -> key) + "->" + printCaminho(raiz -> esquerda) + to_string(raiz -> key) + "->" + printCaminho(raiz -> direita);
		}
	}
}
*/

int main() {
	//Arvore 1
	NoArvore *raiz = NULL;
	inserir(raiz, 15);
	inserir(raiz, 10);
	inserir(raiz, 7);
	inserir(raiz, 11);
	inserir(raiz, 23);
	inserir(raiz, 12);
	inserir(raiz, 1);
	//Arvore 2
	NoArvore *raiz2 = NULL;
	inserir(raiz2, 15);
	inserir(raiz2, 10);
	inserir(raiz2, 7);
	inserir(raiz2, 11);
	inserir(raiz2, 23);
	inserir(raiz2, 12);
	inserir(raiz2, 1);
	//Arvore 3
	NoArvore *raiz3 = NULL;
	inserir(raiz3, 3);
	inserir(raiz3, 2);
	inserir(raiz3, 1);
	inserir(raiz3, 4);
	//Arvore 4
	NoArvore *raiz4 = NULL;
	inserirTrio(raiz4, 7);
	inserirTrio(raiz4, 3);
	inserirTrio(raiz4, 4);
	//Arvore 5
	NoArvore *raiz5 = NULL;
	inserirTrio(raiz5, 12);
	inserirTrio(raiz5, 3);
	inserirTrio(raiz5, 4);
	
	//Questao 1
	cout << "Arvore 1 em Ordem: ";
	exibirArvoreOrdem(raiz);
	cout << endl;
	
	//Questao 2
	cout << "Arvore 1 e 2 sao iguais? " << boolalpha;
	cout << sameBST(raiz, raiz2);
	cout << endl;
	
	//Questao 3
	cout << "Arvore 1 em Pre Ordem: ";
	exibirArvorePreOrdem(raiz);
	cout << endl;
	
	//Questao 4
	cout << "Arvore 1 em Pos Ordem: ";
	exibirArvorePosOrdem(raiz);
	cout << endl;
	
	/*
	//Questao 5
	cout << "Caminhos: ";
	cout << printCaminho(raiz);
	cout << endl;
	*/
	
	//Questao 6 e 7
	cout << "Altura e Profundidade da arvore 1 = ";
	cout << alturaArvore(raiz);
	cout << endl;
	
	//Questao 8
	cout << "Arvore 1: " << endl;
	exibirArvoreOrdemFb(raiz);
	cout << endl;
	cout << "A arvore 1 esta balanceada? ";
	cout << isBalanced(raiz);
	cout << endl;
	
	//Questao 9
	cout << "balanceando... " << endl;
	balancearArvore(raiz);
	cout << "Arvore 1: " << endl;
	exibirArvoreOrdemFb(raiz);
	cout << endl;
	cout << "A arvore 1 esta balanceada? ";
	cout << isBalanced(raiz);
	cout << endl;
	
	//Questao 10
	cout << "A arvore 1 eh BST? ";
	cout << isBST(raiz);
	cout << endl;
	
	//Questao 11
	inverterArvore(raiz);
	cout << "Arvore 1 invertida: " << endl;
	exibirArvoreOrdem(raiz);
	inverterArvore(raiz);
	cout << endl;
	
	//Questao 12
	cout << "Arvore 1: " << endl;
	exibirArvoreOrdem(raiz);
	cout << endl;
	
	cout << "Arvore 3: " << endl;
	exibirArvoreOrdem(raiz3);
	cout << endl;
	
	cout << "Merge 1 e 3: " << endl;
	exibirArvoreOrdem(mergeArvore(raiz, raiz3));
	cout << endl;
	
	//Questao 13
	cout << "Arvore 4: " << endl;
	exibirArvoreOrdem(raiz4);
	cout << endl;
	cout << "Soma dos filhos igual a raiz? " << somaIgualRaiz(raiz4) <<endl;
	cout << "Arvore 5: " << endl;
	exibirArvoreOrdem(raiz5);
	cout << endl;
	cout << "Soma dos filhos igual a raiz? " << somaIgualRaiz(raiz5) <<endl;
	
	//Questao14
	NoArvoreNaria *raizN1 = new NoArvoreNaria;
	raizN1->key = 1;
	raizN1->primeiroFilho = NULL;
	raizN1->proxIrmao = NULL;
	
	NoArvoreNaria *raizN2 = new NoArvoreNaria;
	raizN2->key = 2;
	raizN2->primeiroFilho = NULL;
	raizN2->proxIrmao = NULL;
	
	NoArvoreNaria *raizN3 = new NoArvoreNaria;
	raizN3->key = 3;
	raizN3->primeiroFilho = NULL;
	raizN3->proxIrmao = NULL;
	
	NoArvoreNaria *raizN4 = new NoArvoreNaria;
	raizN4->key = 4;
	raizN4->primeiroFilho = NULL;
	raizN4->proxIrmao = NULL;
	
	raizN1->primeiroFilho = raizN2;
	raizN2->proxIrmao = raizN3;
	raizN3->proxIrmao = raizN4;
	
	NoArvoreNaria *raizN5 = new NoArvoreNaria;
	raizN5->key = 5;
	raizN5->primeiroFilho = NULL;
	raizN5->proxIrmao = NULL;
	
	NoArvoreNaria *raizN6 = new NoArvoreNaria;
	raizN6->key = 6;
	raizN6->primeiroFilho = NULL;
	raizN6->proxIrmao = NULL;
	
	raizN2->primeiroFilho = raizN5;
	raizN5->proxIrmao = raizN6;
	
	NoArvoreNaria *raizN7 = new NoArvoreNaria;
	raizN7->key = 7;
	raizN7->primeiroFilho = NULL;
	raizN7->proxIrmao = NULL;
	
	raizN4->primeiroFilho = raizN7;
	
	cout << "Arvore n-aria em pos ordem: " << endl;
	posOrdemNaria(raizN1);
	cout << endl;
	//Questao 15
	cout << "Arvore 1: " << endl;
	exibirArvoreOrdem(raiz);
	cout << endl;
	cout << "Soma das folhas da arvore 1: " << somaFolhas(raiz)<<endl;
	
	//Questao 16
	maiorCadaNivel(raiz);
	
	//Questao 17
	cout << "Soma da maior subarvore da arvore 1: " << somaMaiorSubarvore(raiz) << endl;
	
	//Questao 18
	cout << "Vetor = ";
	int vetor[7] = {1, 3, 6, 8, 12, 15, 21};
	for(int i = 0; i<7;i++){
		cout << vetor[i] << " ";
	}
	cout << endl;
	NoArvore *raiz6 = arrayParaArvore(vetor, 7);
	cout << "Arvore 6: " << endl;
	exibirArvoreOrdem(raiz6);
	cout << endl;
	
	//Questao 19
	cout << "Arvore 1: " << endl;
	exibirArvoreOrdem(raiz);
	cout << endl;
	cout << "Maior no da arvore 1: " << maiorBST(raiz) -> key << endl;
	
	//Questao 20
	cout << "Menor no da arvore 1: " << menorBST(raiz) -> key << endl;
	
	//Questao 21
	cout << "Busca binaria pelo 3 na arvore 1: " << endl;
	resultadoBuscaBinaria(raiz, 3);
	cout << "Busca binaria pelo 7 na arvore 1: " << endl;
	resultadoBuscaBinaria(raiz, 7);
	return 0;
}
