#include <allegro5/allegro_primitives.h>
#include "menu.h"
#include <stdbool.h>
#include "sceneManager.h"
/*
   [Menu function]
*/
Scene *New_Menu(int label)
{
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    if(window2==0){
        pDerivedObj->background = al_load_bitmap("assets/image/op.jpg");
    }
    else if(window2==1){
        pDerivedObj->background = al_load_bitmap("assets/image/menu.jpg");
    }
    else if(window2==2){
        pDerivedObj->background = al_load_bitmap("assets/image/op1.jpg");
    }
    else if(window2==3){
        pDerivedObj->background = al_load_bitmap("assets/image/op2.jpg");
    }
    else if(window2==4){
        pDerivedObj->background = al_load_bitmap("assets/image/op3.jpg");
    }
    else if(window2==5){
        pDerivedObj->background = al_load_bitmap("assets/image/op4.jpg");
    }
    else if(window2==6){
        pDerivedObj->background = al_load_bitmap("assets/image/dead.jpg");
    }
    else if(window2==7){
        pDerivedObj->background = al_load_bitmap("assets/image/about.jpg");
    }
    else if(window2==8){
        pDerivedObj->background = al_load_bitmap("assets/image/end.jpg");
    }
    else if(window2==9){
        pDerivedObj->background = al_load_bitmap("assets/image/end1.jpg");
    }
    else if(window2==10){
        pDerivedObj->background = al_load_bitmap("assets/image/end2.jpg");
    }
    else if(window2==11){
        pDerivedObj->background = al_load_bitmap("assets/image/end3.jpg");
    }
    else if(window2==12){
        pDerivedObj->background = al_load_bitmap("assets/image/end4.jpg");
    }
    else if(window2==13){
        pDerivedObj->background = al_load_bitmap("assets/image/end5.jpg");
    }
    else if(window2==14){
        pDerivedObj->background = al_load_bitmap("assets/image/end6.jpg");
    }
    else if(window2==15){
        pDerivedObj->background = al_load_bitmap("assets/image/end7.jpg");
    }
    else if(window2==16){
        pDerivedObj->background = al_load_bitmap("assets/image/end8.jpg");
    }
    else if(window2==17){
        pDerivedObj->background = al_load_bitmap("assets/image/end9.jpg");
    }
    else if(window2==18){
        pDerivedObj->background = al_load_bitmap("assets/image/end10.jpg");
    }
    else if(window2==19){
        pDerivedObj->background = al_load_bitmap("assets/image/end11.jpg");
    }
    Scene *pObj = New_Scene(label);
    // setting derived object member
    //pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/bgm2.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->song2 = al_load_sample("assets/sound/drop.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance2 = al_create_sample_instance(pDerivedObj->song2);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // Loop the song until the display closes
    (pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    (pDerivedObj->sample_instance2, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance2, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}
void menu_update(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));  
    if(window2==0){
        if (key_state[ALLEGRO_KEY_B])
        {
            window2++;
            create_scene(Menu_L);
        }
    }
    if(window2==1){
        if (key_state[ALLEGRO_KEY_U])
        {
            window2++;
            create_scene(Menu_L);
        }
        if (key_state[ALLEGRO_KEY_ENTER])
        {
            self->scene_end = true;
            window=1;
        }
        if (key_state[ALLEGRO_KEY_A])
        {
            window2=7;
            create_scene(Menu_L);
        }
    }
    if(window2==2){
        if (prev_key_state[ALLEGRO_KEY_L]==0&&key_state[ALLEGRO_KEY_L]==1)
        {
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_L]=prev_key_state[ALLEGRO_KEY_L];
        }
        
    }
    if(window2==3){
        if (prev_key_state[ALLEGRO_KEY_L]==0&&key_state[ALLEGRO_KEY_L]==1)
        {
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_L]=prev_key_state[ALLEGRO_KEY_L];
            al_play_sample_instance(Obj->sample_instance2);
        }
    }
    if(window2==4){
        if (key_state[ALLEGRO_KEY_Y])
        {
            window2++;
            create_scene(Menu_L);
        }
    }
    if(window2==5){
        if (key_state[ALLEGRO_KEY_ENTER])
        {
            self->scene_end = true;
            window=1;
        }
    }
    if(window2==6){
        if (key_state[ALLEGRO_KEY_M])
        {
            window2=1;
            pass=0;
            create_scene(Menu_L);
        }
    }
    if(window2==7){
        if (key_state[ALLEGRO_KEY_M])
        {
            window2=1;
            create_scene(Menu_L);
        }
    }
    if(window2==8){
        count--;
        if(count==940){
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_ENTER]=prev_key_state[ALLEGRO_KEY_ENTER];
        }
    }
    if(window2==9){
        count--;
        if(count==880){
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_ENTER]=prev_key_state[ALLEGRO_KEY_ENTER];
        }
    }
    if(window2==10){
        count--;
        if(count==820){
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_ENTER]=prev_key_state[ALLEGRO_KEY_ENTER];
        }
    }
    if(window2==11){
        count--;
        if(count==760){
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_ENTER]=prev_key_state[ALLEGRO_KEY_ENTER];
        }
    }
    if(window2==12){
        count--;
        if(count==700){
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_ENTER]=prev_key_state[ALLEGRO_KEY_ENTER];
        }
    }
    if(window2==13){
        count--;
        if(count==670){
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_ENTER]=prev_key_state[ALLEGRO_KEY_ENTER];
        }
    }
    if(window2==14){
        count--;
        if(count==640){
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_ENTER]=prev_key_state[ALLEGRO_KEY_ENTER];
        }
    }
    if(window2==15){
        count--;
        if(count==610){
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_ENTER]=prev_key_state[ALLEGRO_KEY_ENTER];
        }
    }
    if(window2==16){
        count--;
        if(count==580){
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_ENTER]=prev_key_state[ALLEGRO_KEY_ENTER];
        }
    }
    if(window2==17){
        count--;
        if(count==550){
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_ENTER]=prev_key_state[ALLEGRO_KEY_ENTER];
        }
    }
    if(window2==18){
        count--;
        if(count==490){
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_ENTER]=prev_key_state[ALLEGRO_KEY_ENTER];
        }
    }
    if(window2==19){
        if(count==430){
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_ENTER]=prev_key_state[ALLEGRO_KEY_ENTER];
        }
    }
    
    /*if (prev_key_state[ALLEGRO_KEY_SPACE]==0&&key_state[ALLEGRO_KEY_SPACE]==1)
        {
            window2++;
            create_scene(Menu_L);
            key_state[ALLEGRO_KEY_SPACE]=prev_key_state[ALLEGRO_KEY_SPACE];
        }
    else if(key_state[ALLEGRO_KEY_ENTER])
    {
        self->scene_end = true;
        window=1;
    }*/
    return;
}
void menu_draw(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    //al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    //al_draw_rectangle(Obj->title_x - 150, Obj->title_y - 30, Obj->title_x + 150, Obj->title_y + 30, al_map_rgb(255, 255, 255), 0);
    al_play_sample_instance(Obj->sample_instance);
}
void menu_destroy(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    //al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}
