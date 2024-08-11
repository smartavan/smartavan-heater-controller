#pragma once

#include "TrumaStructs.h"
#include "TrumaStructsAlde.h"
#include "helpers.h"

namespace esphome {
namespace truma_inetbox {

inline void status_frame_create_empty(StatusFrame *response, u_int8_t message_type, u_int8_t message_length,
                                      u_int8_t command_counter) {
  response->genericHeader.service_identifier = LIN_SID_READ_STATE_BUFFER | LIN_SID_RESPONSE;
  // Copy header over for this message.
  for (size_t i = 1; i < truma_message_header.size(); i++) {
    response->raw[i] = truma_message_header[i];
  }
  // ALDE has in 5th byte the total msg length including header.
  response->raw[4] = message_length + 6;  // std::max(message_length + 6, 0x1A);

  response->genericHeader.header_2 = 'T';
  response->genericHeader.header_3 = 0x01;
  response->genericHeader.message_type = message_type;
  response->genericHeader.message_length = message_length;
  response->genericHeader.command_counter = command_counter;
}

inline void status_frame_calculate_checksum(StatusFrame *response) {
  response->genericHeader.checksum = 0x0;
  response->genericHeader.checksum = data_checksum(&response->raw[10], response->raw[4], 0);
}

inline void status_frame_create_init(StatusFrame *response, u_int8_t *response_len, u_int8_t command_counter) {
  memset(response->raw, 0x00, sizeof(response->raw));

  status_frame_create_empty(response, STATUS_FRAME_RESPONSE_INIT_REQUEST, 2, command_counter);

  // Set length of package.
  response->raw[4] = 0x1A;
  // Init frame is empty.

  status_frame_calculate_checksum(response);
  (*response_len) = sizeof(StatusFrameHeader) + 20;
}

inline void status_frame_create_null(StatusFrame *response, u_int8_t *response_len) {
  memset(response, 0xFF, 48);

  response->genericHeader.service_identifier = LIN_SID_READ_STATE_BUFFER | LIN_SID_RESPONSE;
  // Copy header over for this message.
  for (size_t i = 1; i < truma_message_header.size(); i++) {
    response->raw[i] = truma_message_header[i];
  }
  // ALDE has in 5th byte the total msg length including header.
  response->raw[4] = 0x1A;

  (*response_len) = 0x25;
}

inline void status_frame_create_init_debug(StatusFrame *response, u_int8_t message_type, u_int8_t *response_len,
                                           u_int8_t command_counter) {
  status_frame_create_empty(response, message_type, 0, command_counter);

  // Init frame is empty.

  status_frame_calculate_checksum(response);
  (*response_len) = sizeof(StatusFrameHeader) + 0;
}

}  // namespace truma_inetbox
}  // namespace esphome
