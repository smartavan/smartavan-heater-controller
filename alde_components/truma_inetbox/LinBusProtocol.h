#pragma once

#include <queue>
#include "LinBusListener.h"

namespace esphome {
namespace truma_inetbox {
class LinBusProtocol : public LinBusListener {
 public:
  virtual const std::array<u_int8_t, 4> lin_identifier() = 0;
  virtual const std::array<u_int8_t, 3> lin_identifier_version() = 0;
  virtual void lin_heartbeat() = 0;
  virtual void lin_reset_device();

 protected:
  const std::array<u_int8_t, 8> lin_empty_response_ = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  bool answer_lin_order_(const u_int8_t pid) override;
  void lin_message_recieved_(const u_int8_t pid, const u_int8_t *message, u_int8_t length) override;

  virtual u_int8_t lin_read_field_by_identifier_(u_int8_t identifier, std::array<u_int8_t, 5> *response) = 0;
  virtual const u_int8_t *lin_multiframe_recieved(const u_int8_t *message, const u_int8_t message_len,
                                                  u_int8_t *return_len) = 0;
  void clear_updates_to_send_queue_() {
    std::queue<std::array<u_int8_t, 8>> empty;
    std::swap(this->updates_to_send_, empty);
  }

  std::queue<std::array<u_int8_t, 8>> updates_to_send_ = {};
  std::array<u_int8_t, 8> updates_to_send_high_prio_ = {};
  bool updates_to_send_high_prio_ready_to_send_ = false;

 private:
  u_int8_t lin_node_address_ = /*LIN initial node address*/ 0x03;

  void prepare_update_msg_(const std::array<u_int8_t, 8> message) { this->updates_to_send_.push(std::move(message)); }
  void prepare_update_msg_high_prio_(const std::array<u_int8_t, 8> message) {
    this->updates_to_send_high_prio_ = message;
    this->updates_to_send_high_prio_ready_to_send_ = true;
  }
  bool is_matching_identifier_(const u_int8_t *message);

  u_int16_t multi_pdu_message_expected_size_ = 0;
  u_int8_t multi_pdu_message_len_ = 0;
  u_int8_t multi_pdu_message_frame_counter_ = 0;
  u_int8_t multi_pdu_message_[64];
  void lin_msg_diag_single_(const u_int8_t *message, u_int8_t length);
  void lin_msg_diag_first_(const u_int8_t *message, u_int8_t length);
  bool lin_msg_diag_consecutive_(const u_int8_t *message, u_int8_t length);
  void lin_msg_diag_multi_();
};

}  // namespace truma_inetbox
}  // namespace esphome