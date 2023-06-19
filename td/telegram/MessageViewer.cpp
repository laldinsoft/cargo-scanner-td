//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2023
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "td/telegram/MessageViewer.h"

#include "td/telegram/ContactsManager.h"

#include "td/utils/algorithm.h"

namespace td {

MessageViewer::MessageViewer(telegram_api::object_ptr<telegram_api::readParticipantDate> &&read_date)
    : MessageViewer(UserId(read_date->user_id_), read_date->date_) {
}

td_api::object_ptr<td_api::messageViewer> MessageViewer::get_message_viewer_object(
    ContactsManager *contacts_manager) const {
  return td_api::make_object<td_api::messageViewer>(
      contacts_manager->get_user_id_object(user_id_, "get_message_viewer_object"), date_);
}

bool operator==(const MessageViewer &lhs, const MessageViewer &rhs) {
  return lhs.user_id_ == rhs.user_id_ && lhs.date_ == rhs.date_;
}

bool operator!=(const MessageViewer &lhs, const MessageViewer &rhs) {
  return !(lhs == rhs);
}

StringBuilder &operator<<(StringBuilder &string_builder, const MessageViewer &viewer) {
  return string_builder << '[' << viewer.user_id_ << " at " << viewer.date_ << ']';
}

MessageViewers::MessageViewers(vector<telegram_api::object_ptr<telegram_api::storyView>> &&story_views) {
  for (auto &story_view : story_views) {
    UserId user_id(story_view->user_id_);
    if (!user_id.is_valid()) {
      LOG(ERROR) << "Receive " << user_id << " as story viewer";
      continue;
    }
    message_viewers_.emplace_back(user_id, story_view->date_);
  }
}

MessageViewers::MessageViewers(vector<telegram_api::object_ptr<telegram_api::readParticipantDate>> &&read_dates)
    : message_viewers_(
          transform(std::move(read_dates), [](telegram_api::object_ptr<telegram_api::readParticipantDate> &&read_date) {
            return MessageViewer(std::move(read_date));
          })) {
}

MessageViewers MessageViewers::get_sublist(const MessageViewer &offset, int32 limit) const {
  MessageViewers result{vector<telegram_api::object_ptr<telegram_api::storyView>>()};
  bool found = offset == MessageViewer(UserId(), 0);
  for (auto &message_viewer : message_viewers_) {
    if (found) {
      if (limit-- <= 0) {
        break;
      }
      result.message_viewers_.push_back(message_viewer);
    } else if (message_viewer == offset) {
      found = true;
    }
  }
  return result;
}

td_api::object_ptr<td_api::messageViewers> MessageViewers::get_message_viewers_object(
    ContactsManager *contacts_manager) const {
  return td_api::make_object<td_api::messageViewers>(
      transform(message_viewers_, [contacts_manager](const MessageViewer &message_viewer) {
        return message_viewer.get_message_viewer_object(contacts_manager);
      }));
}

StringBuilder &operator<<(StringBuilder &string_builder, const MessageViewers &viewers) {
  return string_builder << viewers.message_viewers_;
}

}  // namespace td
