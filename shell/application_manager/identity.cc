// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "shell/application_manager/identity.h"

#include "shell/application_manager/query_util.h"

namespace shell {

Identity::Identity(const GURL& url, const std::string& qualifier)
    : url(GetBaseURLAndQuery(url, nullptr)), qualifier(qualifier) {
}

Identity::Identity(const GURL& base_url)
    : url(GetBaseURLAndQuery(base_url, nullptr)), qualifier(url.spec()) {
}

bool Identity::operator<(const Identity& other) const {
  if (url != other.url)
    return url < other.url;
  return qualifier < other.qualifier;
}

}  // namespace shell
