

//rotate functions wrap around unlike shifts
void frame_rotate_right(FrameTypeDef frame,uint8_t repetition);
void frame_rotate_left(FrameTypeDef frame,uint8_t repetition);
void frame_rotate_forward(FrameTypeDef frame,uint8_t repetition);
void frame_rotate_back(FrameTypeDef frame,uint8_t repetition);
void frame_rotate_up(FrameTypeDef frame,uint8_t repetition);
void frame_rotate_down(FrameTypeDef frame,uint8_t repetition);

//shift functions don't wrap around unlike rotates
void frame_shift_right(FrameTypeDef frame,uint8_t repetition);
void frame_shift_left(FrameTypeDef frame,uint8_t repetition);
void frame_shift_forward(FrameTypeDef frame,uint8_t repetition);
void frame_shift_back(FrameTypeDef frame,uint8_t repetition);
void frame_shift_up(FrameTypeDef frame,uint8_t repetition);
void frame_shift_down(FrameTypeDef frame,uint8_t repetition);


void frame_brighten_add(uint16_t brightnessDelta);
void frame_brighten_shift(uint16_t shiftAmount);
void frame_brighten_rotate(uint16_t rotateAmount);

void frame_dim_subtract(uint16_t brightnessDelta);
void frame_dim_shift(uint16_t shiftAmount);
void frame_dim_rotate(uint16_t rotateAmount);

void frame_set_red(uint16_t brightness, bool mask[64]);
void frame_set_grn(uint16_t brightness, bool mask[64]);
void frame_set_blu(uint16_t brightness, bool mask[64]);
