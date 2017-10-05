struct estrutura{
    int posicaoX;
    int posicaoY;
    double custoF;
    double heuristica;
};

typedef struct elemento* Lista;

Lista* cria_lista();

void libera_lista(Lista* li);

int insere_lista_ordenada(Lista* li, struct estrutura al);

int insere_inicio(Lista* li, struct estrutura al);

int remove_lista_inicio(Lista* li);

int remove_lista(Lista* li, int x, int y);

int tamanho_lista(Lista* li);

int lista_vazia(Lista* li);

int lista_cheia(Lista* li);

struct estrutura consulta_lista(Lista* li);

int verificaIgual(Lista* li, int x, int y);

void imprimeLista(Lista* li);

struct estrutura consulta_Ponto(Lista* li, int x, int y);

