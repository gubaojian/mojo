// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "shell/shell_test_helper.h"

#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/logging.h"
#include "base/path_service.h"
#include "shell/filename_util.h"
#include "shell/init.h"
#include "shell/mojo_url_resolver.h"

namespace mojo {
namespace shell {

ShellTestHelper::ShellTestHelper() {
  base::CommandLine::Init(0, NULL);
  mojo::shell::InitializeLogging();
}

ShellTestHelper::~ShellTestHelper() {
}

void ShellTestHelper::Init() {
  context_.Init();
  test_api_.reset(
      new ApplicationManager::TestAPI(context_.application_manager()));
  base::FilePath service_dir;
  CHECK(PathService::Get(base::DIR_MODULE, &service_dir));
  context_.mojo_url_resolver()->SetBaseURL(FilePathToFileURL(service_dir));
}

void ShellTestHelper::SetLoaderForURL(scoped_ptr<ApplicationLoader> loader,
                                      const GURL& url) {
  context_.application_manager()->SetLoaderForURL(loader.Pass(), url);
}

void ShellTestHelper::AddCustomMapping(const GURL& mojo_url,
                                       const GURL& resolved_url) {
  context_.mojo_url_resolver()->AddCustomMapping(mojo_url, resolved_url);
}

}  // namespace shell
}  // namespace mojo