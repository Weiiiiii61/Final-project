#include "charater.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
//#include <Windows.h>
#include <stdbool.h>
/*
   [Character function]
*/
Elements *New_Character(int label)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    char state_string[4][10] = {"stop", "move", "attack","down"};
    for (int i = 0; i < 4; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *squat = al_load_sample("assets/sound/squat.mp3");
    pDerivedObj->squat_Sound = al_create_sample_instance(squat);
    al_set_sample_instance_playmode(pDerivedObj->squat_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->squat_Sound, al_get_default_mixer());    
    ALLEGRO_SAMPLE *jump = al_load_sample("assets/sound/jump.mp3");
    pDerivedObj->jump_Sound = al_create_sample_instance(jump);
    al_set_sample_instance_playmode(pDerivedObj->jump_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->jump_Sound, al_get_default_mixer());



    // initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 0;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 15;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    return pObj;
}
void Character_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Character *chara = ((Character *)(self->pDerivedObj));
    Shape *hitbox = chara->hitbox;
    if(a==0){
    if (chara->state == STOP)
    {
        if(chara->y<=310){
            _Character_update_position(self, 0, 7);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = true;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = MOVE;
            al_play_sample_instance(chara->jump_Sound);
            a=1;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = false;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_LCTRL]||key_state[ALLEGRO_KEY_RCTRL])
        {
            chara->y=380;
            al_play_sample_instance(chara->squat_Sound);
            hitbox->update_center_y(hitbox, 70);
            chara->state = DOWN;
        }
        
        else
        {
            chara->state = STOP;
        }

    }
    else if (chara->state == MOVE)
    {
        if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = true;
            _Character_update_position(self, -5, 0);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_LCTRL]||key_state[ALLEGRO_KEY_RCTRL])
        {
            chara->y=380;
            al_play_sample_instance(chara->squat_Sound);
            hitbox->update_center_y(hitbox, 70);
            chara->state = DOWN;
        }
        else if (prev_key_state[ALLEGRO_KEY_SPACE]==0&&key_state[ALLEGRO_KEY_SPACE]==1)
        {
            al_play_sample_instance(chara->jump_Sound);
            a=1;
            key_state[ALLEGRO_KEY_SPACE]=prev_key_state[ALLEGRO_KEY_SPACE];
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = false;
            _Character_update_position(self, 5, 0);
            chara->state = MOVE;
        }
        if(chara->y<=310){
            _Character_update_position(self, 0, 7);
            chara->state = MOVE;
        }
        if (chara->gif_status[chara->state]->done){
            chara->state = STOP;
        }
    }
    else if(chara->state==DOWN){
       if (key_state[ALLEGRO_KEY_A])
        {
            chara->y=310;
            hitbox->update_center_y(hitbox, -70);
            chara->dir = true;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->y=310;
            hitbox->update_center_y(hitbox, -70);
            chara->dir = false;
            chara->state = MOVE;
        }
        /*if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->y=310;
            al_play_sample_instance(chara->atk_Sound);
            hitbox->update_center_y(hitbox, -70);
            chara->state = MOVE;
            a=1;
        }*/
        if(chara->y<=310){
            _Character_update_position(self, 0, 7);
            chara->state = MOVE;
        }
        if (chara->gif_status[chara->state]->done){
            chara->y=310;
            chara->state = STOP;
            hitbox->update_center_y(hitbox, -70);
        }
    }
    }
    if(a==1){
        if(chara->y>130){
            _Character_update_position(self, 0, -7);
            chara->state = ATK;
        }
        else{
            a=0;
            chara->state = MOVE;
        }
    }
    
}
void Character_draw(Elements *self)
{
    // with the state, draw corresponding image
    Character *chara = ((Character *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    /*if (prev_key_state[ALLEGRO_KEY_SPACE]==0&&key_state[ALLEGRO_KEY_SPACE]==1)
    {
        al_play_sample_instance(chara->jump_Sound);
    }
    else if (chara->state == DOWN && chara->gif_status[chara->state]->display_index == 2)
    {
        al_play_sample_instance(chara->squat_Sound);
    }*/
}
void Character_destory(Elements *self)
{
    Character *Obj = ((Character *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->jump_Sound);
    al_destroy_sample_instance(Obj->squat_Sound);
    for (int i = 0; i < 4; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Character_update_position(Elements *self, int dx, int dy)
{
    Character *chara = ((Character *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Character_interact(Elements *self, Elements *tar) {}
