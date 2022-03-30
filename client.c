#include "client.h"

/* Função principal de um Cliente. Deve executar um ciclo infinito onde em 
* cada iteração lê uma operação da main e data->terminate ainda for igual a 0,
* processa-a e guarda o resultado no histórico de operações da Main.
* Operações com id igual a -1 são ignoradas (op inválida) e se
* data->terminate for igual a 1 é porque foi dada ordem de terminação do programa,
* portanto deve-se fazer return do o número de operações processadas. Para efetuar
* estes passos, pode usar os outros métodos auxiliares definidos em client.h. 
*/
int execute_client(int client_id, struct communication_buffers* buffers, struct main_data* data) {

    int count = 0;
    while(1){

        if (data -> terminate == 0){
            count+=1;
            client_get_operation(data->results, client_id, buffers, data);

            if(buffers->driv_cli->buffer->id != -1){
                client_process_operation (data->results, client_id, data, count);    
                            
                if (data->terminate == 1) {
                    return count;
                }
            }
        }
    }
}

/* Função que lê uma operação do buffer de memória partilhada entre os motoristas
* e clientes que seja direcionada a client_id. Antes de tentar ler a operação, deve
* verificar se data->terminate tem valor 1. Em caso afirmativo, retorna imediatamente da função.
*/
void client_get_operation(struct operation* op, int client_id, struct communication_buffers* buffers, struct main_data* data) {

    if ((*data->terminate == 1)){
        return;
    }
    read_driver_client_buffer(buffers->driv_cli, client_id, data->buffers_size, op);
}

/* Função que processa uma operação, alterando o seu campo receiving_client para o id
* passado como argumento, alterando o estado da mesma para 'C' (client), e 
* incrementando o contador de operações. Atualiza também a operação na estrutura data.
*/
void client_process_operation(struct operation* op, int client_id, struct main_data* data, int* counter) {
    
    op->receiving_client = client_id;
    op->status = 'C';
    data->results->status = op->status;
    counter++;
}