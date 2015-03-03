## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

def build(bld):
    obj = bld.create_ns3_module('hr-wpan', ['core', 'network', 'mobility', 'spectrum', 'propagation'])
    obj.source = [
        'model/mac/hr-wpan-mac-header.cc',
        'model/mac/hr-wpan-mac-trailer.cc',
		'model/mac/hr-wpan-dev-id.cc',
		'model/mac/sap/hr-wpan-mac-sap.cc',
		'model/mac/sap/hr-wpan-mac-sap-async.cc',
		'model/mac/sap/hr-wpan-mac-sap-isoch.cc',
		'model/mac/sap/hr-wpan-mac-sap-start.cc',
		'model/mac/hr-wpan-mac.cc',
		'model/channel/hr-wpan-spectrum-signal-parameters.cc',
		'model/channel/hr-wpan-error-model.cc',
		'model/phy/messages/hr-wpan-phy-control-message.cc',
		'model/phy/messages/hr-wpan-phy-control-message-factory.cc',
		'model/phy/beamforming/hr-wpan-phy-ula-antenna.cc',
		'model/phy/beamforming/hr-wpan-phy-ula-beamforming.cc',
		'model/phy/beamforming/hr-wpan-phy-ula-params.cc',
		'model/phy/hr-wpan-phy.cc',
		'model/devices/hr-wpan-net-device.cc',
		'model/phy/states/hr-wpan-phy-abs-state.cc',
		'model/phy/states/hr-wpan-phy-idle-state.cc',
		'model/phy/states/hr-wpan-phy-rx-on-state.cc',
		'model/phy/states/hr-wpan-phy-rx-busy-state.cc',
		'model/phy/states/hr-wpan-phy-tx-on-state.cc',
		'model/phy/states/hr-wpan-phy-tx-busy-state.cc',
		'model/phy/states/hr-wpan-phy-switch-state.cc',
		'model/phy/states/hr-wpan-phy-state-factory.cc',
		'helper/phy/hr-wpan-spectrum-model-factory.cc',
		'helper/phy/hr-wpan-spectrum-value-helper.cc',
		'helper/phy/hr-wpan-interference-helper.cc',
		'helper/hr-wpan-helper.cc',
		
        ]

    module_test = bld.create_ns3_module_test_library('hr-wpan')

    module_test.source = [
        'test/hr-wpan-packet-test.cc',
		'test/hr-wpan-spectrum-value-helper-test.cc',
		'test/hr-wpan-ula-beamforming-test.cc',
		'test/hr-wpan-phy-state-test.cc',
		'test/hr-wpan-mac-queue-test.cc'
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
		'model/phy/messages/hr-wpan-phy-control-message.h',
		'model/phy/messages/hr-wpan-phy-control-message-factory.h',
		'model/phy/beamforming/hr-wpan-phy-ula-antenna.h',
		'model/phy/beamforming/hr-wpan-phy-ula-beamforming.h',
		'model/phy/beamforming/hr-wpan-phy-ula-params.h',
		'model/phy/hr-wpan-phy-user.h',
		'model/phy/hr-wpan-phy-provider.h',
		'model/phy/hr-wpan-phy.h',
		'model/phy/hr-wpan-phy-attributes.h',
		'model/phy/states/hr-wpan-phy-abs-state.h',
		'model/phy/states/hr-wpan-phy-idle-state.h',
		'model/phy/states/hr-wpan-phy-rx-on-state.h',
		'model/phy/states/hr-wpan-phy-rx-busy-state.h',
		'model/phy/states/hr-wpan-phy-tx-on-state.h',
		'model/phy/states/hr-wpan-phy-tx-busy-state.h',
		'model/phy/states/hr-wpan-phy-switch-state.h',
		'model/phy/states/hr-wpan-phy-state-factory.h',
		'model/devices/hr-wpan-net-device.h',
		'model/mac/sap/hr-wpan-mac-sap.h',
		'model/mac/sap/hr-wpan-mac-sap-async.h',
		'model/mac/sap/hr-wpan-mac-sap-isoch.h',
		'model/mac/sap/hr-wpan-mac-sap-start.h',
		'model/mac/hr-wpan-mac-pib.h'
		'helper/phy/hr-wpan-spectrum-model-factory.h',
		'helper/phy/hr-wpan-spectrum-value-helper.h',
		'helper/phy/hr-wpan-interference-helper.h',
		'helper/hr-wpan-helper.h',
        ]

    if (bld.env['ENABLE_EXAMPLES']):
		bld.recurse('examples')

    #bld.ns3_python_bindings()
