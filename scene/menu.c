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

    Scene *pObj = New_Scene(label);
    // setting derived object member
    //pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/bgm1.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // Loop the song until the display closes
    (pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
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
