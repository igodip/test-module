## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

def build(bld):
    obj = bld.create_ns3_module('hr-wpan', ['core', 'network', 'mobility', 'spectrum', 'propagation'])
    obj.source = [
        'model/hr-wpan-error-model.cc',
        'model/hr-wpan-interference-helper.cc',
        'model/hr-wpan-phy.cc',
        'model/hr-wpan-mac.cc',
        'model/hr-wpan-mac-header.cc',
        'model/hr-wpan-mac-trailer.cc',
        'model/hr-wpan-csmaca.cc',
        'model/hr-wpan-net-device.cc',
        'model/hr-wpan-spectrum-value-helper.cc',
        'model/hr-wpan-spectrum-signal-parameters.cc',
        'model/hr-wpan-lqi-tag.cc',
		'model/hr-wpan-dev-id.cc',
        'helper/hr-wpan-helper.cc',
        ]

    module_test = bld.create_ns3_module_test_library('hr-wpan')

	
    module_test.source = []
    #    'test/lr-wpan-ack-test.cc',
    #    'test/lr-wpan-cca-test.cc',
    #    'test/lr-wpan-collision-test.cc',
    #   'test/lr-wpan-ed-test.cc',
    #   'test/lr-wpan-error-model-test.cc',
    #    'test/lr-wpan-packet-test.cc',
    #    'test/lr-wpan-pd-plme-sap-test.cc',
    #   'test/lr-wpan-spectrum-value-helper-test.cc',
    #    ]
     
    headers = bld(features='ns3header')
    headers.module = 'hr-wpan'
    headers.source = [
        'model/hr-wpan-error-model.h',
        'model/hr-wpan-interference-helper.h',
        'model/hr-wpan-phy.h',
        'model/hr-wpan-mac.h',
        'model/hr-wpan-mac-header.h',
        'model/hr-wpan-mac-trailer.h',
        'model/hr-wpan-csmaca.h',
        'model/hr-wpan-net-device.h',
        'model/hr-wpan-spectrum-value-helper.h',
        'model/hr-wpan-spectrum-signal-parameters.h',
        'model/hr-wpan-lqi-tag.h',
		'model/hr-wpan-dev-id.h'
        'helper/hr-wpan-helper.h',
        ]

    if (bld.env['ENABLE_EXAMPLES']):
        bld.recurse('examples')

    #bld.ns3_python_bindings()
