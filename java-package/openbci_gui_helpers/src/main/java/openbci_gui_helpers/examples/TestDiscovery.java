package openbci_gui_helpers.examples;

import java.util.Map;

import openbci_gui_helpers.GUIHelper;
import openbci_gui_helpers.GanglionError;

public class TestDiscovery
{

    public static void main (String[] args) throws GanglionError
    {
        Map<String, String> map = GUIHelper.scan_for_ganglions (args[0], 3);
        for (Map.Entry<String, String> entry : map.entrySet ())
        {
            System.out.println ("Key = " + entry.getKey () + ", Value = " + entry.getValue ());
        }
    }
}
