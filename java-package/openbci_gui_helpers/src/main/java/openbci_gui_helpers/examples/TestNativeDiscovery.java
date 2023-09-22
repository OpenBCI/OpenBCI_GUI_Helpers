package openbci_gui_helpers.examples;

import openbci_gui_helpers.GUIHelper;
import openbci_gui_helpers.GanglionDevice;
import openbci_gui_helpers.GanglionError;

public class TestNativeDiscovery {

    public static void main(String[] args) throws GanglionError {
        GanglionDevice[] devices = GUIHelper.scan_for_ganglions(3);
        for (GanglionDevice device : devices) {
            System.out.println("Identifier = " + device.identifier + ", Mac Address = " + device.mac_address
                    + ", Firmware = " + device.firmware_version);
        }
        System.out.println("Completed");
    }
}
