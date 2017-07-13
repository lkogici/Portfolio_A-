typedef struct elemento* Lista;

Lista* cria_lista();

void libera_lista(Lista* li);

int insere_lista_final(Lista* li, struct aluno al);

int insere_lista_inicio(Lista* li, struct aluno al);

int insere_lista_ordenada(Lista* li, struct aluno al);

int remove_lista(Lista* li, int mat);

int remove_lista_inicio(Lista* li);

int remove_lista_final(Lista* li);

int tamanho_lista(Lista* li);

int lista_vazia(Lista* li);

int lista_cheia(Lista* li);

void imprime_lista(Lista* li);

void consulta_lista(Lista* li, int mat);
