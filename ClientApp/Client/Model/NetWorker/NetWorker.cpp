#include "NetWorker.hpp"

NetWorker::NetWorker(){
    __mutex = new pthread_mutex_t;
}

NetWorker::~NetWorker(){
    if(__mutex != nullptr){
        pthread_mutex_destroy(__mutex);
        //delete __mutex;
    }
}

bool NetWorker::openConnection(int client_socket){

    if(pthread_mutex_init(__mutex,nullptr) == -1){
        return false;
    }
    if(client_socket == -1){
        return false;
    }
    __socket = client_socket;
    __status_connection = true;
    __buffer_status_connection = __status_connection;
    qDebug() <<"SOCKET "<< __socket;
    __thread_arguments.object = this;
    __thread_arguments.socket = &__socket;
    __thread_arguments.status_connection = &__status_connection;
    __thread_arguments.buffer_status_connection = &__buffer_status_connection;
    __thread_arguments.message = &__message;
    __thread_arguments.buffer_message = &__buffer_message;
    __thread_arguments.operation = &__operation;
    __thread_arguments.buffer_operation = &__buffer_operation;
    __thread_arguments.mutex = __mutex;


    if(pthread_create(&__thread_id,nullptr,NetWorker::__execute,&__thread_arguments)){
        perror("Error net worker create \"execute\"");
        __status_connection = false;
        return false;
    }
    pthread_detach(__thread_id);

    return true;
}

void NetWorker::setMessage(QByteArray message){
    pthread_mutex_lock(__mutex);
    __buffer_message = message;
    pthread_mutex_unlock(__mutex);
}

void NetWorker::getMessage(QByteArray *message){
    pthread_mutex_lock(__mutex);

    *message = __buffer_message;
    pthread_mutex_unlock(__mutex);
}

void NetWorker::setWorkingMode(OPERATION_MODE mode){
    pthread_mutex_lock(__mutex);

    __buffer_operation = mode;

    pthread_mutex_unlock(__mutex);

}
void NetWorker::getWorkingMode(OPERATION_MODE *mode){
    pthread_mutex_lock(__mutex);

    *mode = __buffer_operation;

    pthread_mutex_unlock(__mutex);
}

void NetWorker::closeConnection(){
    pthread_mutex_lock(__mutex);
    __buffer_status_connection = false;
    pthread_mutex_unlock(__mutex);
}
void NetWorker::isAliveConnection(bool *status_connection){
    pthread_mutex_lock(__mutex);
    *status_connection = __buffer_status_connection;
    pthread_mutex_unlock(__mutex);
}

void NetWorker::__sendMessage(){
    __message += M_END_MESSAGE;
    int step = 0;
    int length_message;
    bool last_step = false;
    int send_message = 0;
    size_t buf_size = __message.size();

    if(buf_size > INT16_MAX){
        step = INT16_MAX;
        length_message = INT16_MAX;
    }
    else{
        step = 0;
        length_message = buf_size;
        last_step = true;
    }

    for(int i = 0; ;i++){
        //qDebug() << "send start";
        if((send_message = send(__socket,(__message.data() + step*i + send_message),length_message,0)) == -1){
            //Сообщения в логи
            qDebug() <<"Error send message, soket: %d" << __socket;
            send_message = 0;
            return;
        }
        //qDebug() <<"MESS "<<__message;
        //qDebug() << "send end";
        if(send_message == length_message){
            send_message = 0;
            if(buf_size <= step*(i+1) + length_message){
                if(last_step){
                    break;
                }

                length_message = buf_size - step*(i+1);
                last_step = true;
            }
        }
        else{
            i--;
            length_message -= send_message;
        }

    }
}
void NetWorker::__reciveMessage(){
    __message.clear();
    char temp_buf[RECIVE_BUFFER_SIZE+1];
    int index_end_message;
    int index_close_connection;

    for(;;){
        memset(temp_buf,0,sizeof(char) * RECIVE_BUFFER_SIZE);

        if(recv(__socket, temp_buf,sizeof(char) * RECIVE_BUFFER_SIZE,0) == -1){
            qDebug() <<"ERROR recive message, socket: ";
            return;
        }
        else{
            __message.push_back(temp_buf);
            if(__message == ""){
                break;
            }
            index_end_message = __message.indexOf(M_END_MESSAGE);
            index_close_connection = __message.indexOf(M_CLOSE_CONNECTION);

            if(index_close_connection != -1){
                __message.remove(index_close_connection,M_CLOSE_CONNECTION.length());
                __status_connection = false;
                break;
            }
            else if(index_end_message != -1){
                __message.remove(index_end_message,M_END_MESSAGE.length());
                break;
            }
        }
    }
}
void* NetWorker::__execute(void *value){
    __net_worket_info_t *arguments = (__net_worket_info_t*)value;
    //qDebug() << "создали";
    for(;*arguments->status_connection;){

        //обновление данных (задач)
        usleep(100);

        pthread_mutex_lock(arguments->mutex);
        *arguments->message = *arguments->buffer_message;
        *arguments->operation = *arguments->buffer_operation;
        *arguments->status_connection = *arguments->buffer_status_connection;
        pthread_mutex_unlock(arguments->mutex);

        switch(*arguments->operation){
            case OPERATION_READ:
                arguments->object->__reciveMessage();
            break;
            case OPERATION_WRITE:
                arguments->object->__sendMessage();
                arguments->message->clear();
            break;
            default:
               continue;
            break;
        }


        *arguments->operation = OPERATION_NONE;

        pthread_mutex_lock(arguments->mutex);
        *arguments->buffer_message = *arguments->message;
        *arguments->buffer_operation = OPERATION_NONE;
        *arguments->buffer_status_connection = *arguments->status_connection;
        pthread_mutex_unlock(arguments->mutex);


}

    arguments->object->__sendMessage();
    arguments->message->clear();

    pthread_mutex_destroy(arguments->mutex);
    close(*arguments->socket);
    pthread_exit(nullptr);
}

