package openbci_gui_helpers.examples;

import java.util.Map;

import openbci_gui_helpers.GUIHelper;
import openbci_gui_helpers.GanglionError;
import openbci_gui_helpers.WIFIInfo;

public class TestWifiDiscovery
{
    public static void main (String[] args) throws GanglionError
    {
        Map<String, WIFIInfo> map = GUIHelper.scan_for_wifi (10);
        for (Map.Entry<String, WIFIInfo> entry : map.entrySet ())
        {
            System.out.println ("Key = " + entry.getKey () + ", Value = " + entry.getValue ());
        }
    }
}
