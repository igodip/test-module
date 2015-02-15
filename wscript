## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

def build(bld):
    obj = bld.create_ns3_module('hr-wpan', ['core', 'network', 'mobility', 'spectrum', 'propagation'])
    obj.source = [
        'model/mac/hr-wpan-mac-header.cc',
        'model/mac/hr-wpan-mac-trailer.cc',
		'model/mac/hr-wpan-dev-id.cc',
		'model/mac/hr-wpan-mac.cc',
		'model/channel/hr-wpan-spectrum-signal-parameters.cc',
		'model/channel/hr-wpan-error-model.cc',
		'model/phy/hr-wpan-phy.cc',
		'model/devices/hr-wpan-net-device.cc',
		'helper/phy/hr-wpan-spectrum-model-factory.cc',
		'helper/phy/hr-wpan-spectrum-value-helper.cc',
		'helper/phy/hr-wpan-interference-helper.cc',
		'helper/hr-wpan-helper.cc'
        ]

    module_test = bld.create_ns3_module_test_library('hr-wpan')

    module_test.source = [
#		'test/hr-wpan-error-model-test.cc',
        'test/hr-wpan-packet-test.cc',
		'test/hr-wpan-spectrum-value-helper-test.cc',
        ]
     
    headers = bld(features='ns3header')
    headers.module = 'hr-wpan'
    headers.source = [
        'model/mac/hr-wpan-mac-header.h',
        'model/mac/hr-wpan-mac-trailer.h',
		'model/mac/hr-wpan-dev-id.h',
		'model/mac/hr-wpan-mac.h',
		'model/channel/hr-wpan-spectrum-signal-parameters.h',
		'model/channel/hr-wpan-error-model.h',
		'model/phy/hr-wpan-phy.h',
		'model/devices/hr-wpan-net-device.cc',
		'helper/phy/hr-wpan-spectrum-model-factory.h',
		'helper/phy/hr-wpan-spectrum-value-helper.h',
		'helper/phy/hr-wpan-interference-helper.h',
		'helper/hr-wpan-helper.h'
        ]

    #if (bld.env['ENABLE_EXAMPLES']):
		
		#bld.recurse('examples')
    #bld.ns3_python_bindings()
