#!/usr/bin/env python

"""
This file generates all telemetry_GpuTest control files from a master list.
"""

# This test list can be obtained by executing
# /build/${BOARD}/usr/local/telemetry/src/content/test/gpu/run_gpu_test.py

TESTS = [
    'context_lost',
    'depth_capture',
    'gpu_process',
    'hardware_accelerated_feature',
    'info_collection',
    'maps',
    'noop_sleep',
    'pixel',
    'screenshot_sync',
    'trace_test',
    'webgl_conformance'
]

CONTROLFILE_TEMPLATE = """\
# Copyright 2014 The Chromium OS Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# Do not edit this file! It was created by generate_controlfiles.py.

AUTHOR = 'chromeos-gfx'
NAME = 'telemetry_GpuTests.{0}'
ATTRIBUTES = 'suite:graphics_per-day, suite:graphics_browser'
TIME = 'LONG'
TEST_CATEGORY = 'Functional'
TEST_CLASS = 'gl'
TEST_TYPE = 'server'

DOC = '''
This server control file executes the GPU telemetry test: {0}.

Pass local=True to run with local telemetry and no AFE server.
'''

from autotest_lib.client.common_lib import utils

def run_test(machine):
    host = hosts.create_host(machine)
    job.run_test('telemetry_GpuTests',
                 host=host,
                 test='{0}',
                 args=utils.args_to_dict(args))


parallel_simple(run_test, machines)\
"""


for test in TESTS:
    filename = 'control.%s' % test
    with open(filename, 'w+') as f:
        content = CONTROLFILE_TEMPLATE.format(test)
        f.write(content)
