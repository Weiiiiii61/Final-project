#include "charater2.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
/*
   [Character function]
*/
Elements *New_Character2(int label)
{
    Character2 *pDerivedObj = (Character2 *)malloc(sizeof(Character2));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    char state_string[3][10] = {"stop", "move", "attack"};
    for (int i = 0; i < 3; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 1050;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 15;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP2;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Character2_draw;
    pObj->Update = Character2_update;
    pObj->Interact = Character2_interact;
    pObj->Destroy = Character2_destory;
    return pObj;
}
void Character2_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Character2 *chara = ((Character2 *)(self->pDerivedObj));
    if (chara->state == STOP2)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK2;
        }
    }
    else if (chara->state == MOVE2)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK2;
        }
    }
    else if (chara->state == ATK2)
    {
        if (chara->gif_status[chara->state]->done)
        {
            chara->state = STOP2;
            chara->new_proj = false;
        }
        if (chara->gif_status[ATK2]->display_index == 2 && chara->new_proj == false)
        {
            Elements *pro;
            if (chara->dir)
            {
                pro = New_Projectile(Projectile_L,
                                     chara->x + chara->width - 100,
                                     chara->y + 10,
                                     5);
            }
            else
            {
                pro = New_Projectile(Projectile_L,
                                     chara->x - 50,
                                     chara->y + 10,
                                     -5);
            }
            _Register_elements(scene, pro);
            chara->new_proj = true;
        }
    }
}
void Character2_draw(Elements *self)
{
    // with the state, draw corresponding image
    Character2 *chara = ((Character2 *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    if (chara->state == ATK2 && chara->gif_status[chara->state]->display_index == 2)
    {
        al_play_sample_instance(chara->atk_Sound);
    }
}
void Character2_destory(Elements *self)
{
    Character2 *Obj = ((Character2 *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Character2_update_position(Elements *self, int dx, int dy)
{
    Character2 *chara = ((Character2 *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Character2_interact(Elements *self, Elements *tar) {}