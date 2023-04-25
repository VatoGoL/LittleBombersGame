#include "ServerApp.hpp"

ServerApp::ServerApp()
{
    __s_renderer = new ServerRenderer;
    __s_manager = new ServerManager(__MAX_PLAYER_COUNT);

    pthread_mutex_init(&__key_mutex, nullptr);
}
ServerApp::~ServerApp()
{
    pthread_mutex_destroy(&__key_mutex);
    delete __s_renderer;
    delete __s_manager;
}
void* ServerApp::__keyReader(void *value){
    key_info_t *object = (key_info_t*)value;
    char keys[ServerApp::SIZE_TEMP_KEY_BUFFER+1];
    for(;;){
        scanf("%s",keys);

        pthread_mutex_lock(object->mutex);
        if(!(*object->key_read)){
            break;
        }
        *object->key_buffer = keys;
        pthread_mutex_unlock(object->mutex);
    }
    pthread_exit(nullptr);
}

void ServerApp::execute()
{
    init();
    int step = 0;
    for(;;){
        pthread_mutex_lock(&__key_mutex);
        __key_command = __key_buffer;
        __key_buffer.clear();
        pthread_mutex_unlock(&__key_mutex);

        if(__key_command.size() > 0){
            if(__key_command == "a"){
                __s_renderer->draw_a();
            }
            else if(__key_command == "b"){
                __s_renderer->draw_b();
            }
            else{

            }
            printf("Count step: %d\n", step);
            step = 0;
        }
        step++;

        //printf("Count step: %d\n", step);
        //__s_rendereprintf("Count step: %d\n", step);
        //r->draw_a();
        //__s_manager->stepExecute();
        sleep(1);
    }
}
void ServerApp::init()
{
    __key_read = true;

    __thread_arguments.mutex = &__key_mutex;
    __thread_arguments.key_read = &__key_read;
    __thread_arguments.key_buffer = &__key_buffer;

    pthread_create(&__key_input_id,nullptr,ServerApp::__keyReader,(void*)&__thread_arguments);
    pthread_detach(__key_input_id);

    __s_manager->initServer();
    printf("Init\n");
}
