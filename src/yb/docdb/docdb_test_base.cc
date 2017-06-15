// Copyright (c) YugaByte, Inc.

#include "yb/docdb/docdb_test_base.h"

#include "yb/docdb/docdb.h"
#include "yb/docdb/docdb_test_util.h"

namespace yb {
namespace docdb {

DocDBTestBase::DocDBTestBase() {
}

DocDBTestBase::~DocDBTestBase() {
}

void DocDBTestBase::SetUp() {
  YBTest::SetUp();
  ASSERT_OK(InitRocksDBOptions());
  ASSERT_OK(InitRocksDBDir());
  ASSERT_OK(OpenRocksDB());
  ResetMonotonicCounter();
}

void DocDBTestBase::TearDown() {
  ASSERT_OK(DestroyRocksDB());
  YBTest::TearDown();
}

void DocDBTestBase::CaptureLogicalSnapshot() {
  logical_snapshots_.emplace_back();
  logical_snapshots_.back().Capture(rocksdb());
}

void DocDBTestBase::ClearLogicalSnapshots() {
  logical_snapshots_.clear();
}

void DocDBTestBase::RestoreToRocksDBLogicalSnapshot(int snapshot_index) {
  CHECK_LE(0, snapshot_index);
  CHECK_LT(snapshot_index, logical_snapshots_.size());
  logical_snapshots_[snapshot_index].RestoreTo(rocksdb());
}

}  // namespace docdb
}  // namespace yb
