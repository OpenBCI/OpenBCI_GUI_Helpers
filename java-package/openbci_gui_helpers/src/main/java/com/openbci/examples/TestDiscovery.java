package com.openbci.examples;

import java.util.Map;

import com.openbci.GUIHelper;
import com.openbci.GanglionError;

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
