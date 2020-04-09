package openbci_gui_helpers.examples;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import openbci_gui_helpers.GanglionError;
import com.vmichalak.protocol.ssdp.Device;
import com.vmichalak.protocol.ssdp.SSDPClient;

public class TestWifiDiscovery
{
    public static void main (String[] args) throws GanglionError, IOException
    {
        List<Device> devices = SSDPClient.discover (3000, "urn:schemas-upnp-org:device:Basic:1");
        System.out.println (devices.size () + " devices found");
        for (int i = 0; i < devices.size (); i++)
        {
            System.out.println ("Location: " + devices.get (i).getIPAddress ());
            System.out.println ("Description: " + devices.get (i).getDescriptionUrl ());
            System.out.println ("Server: " + devices.get (i).getServer ());
            System.out.println ("Service Type: " + devices.get (i).getServiceType ());
            System.out.println ("Device Name: " + devices.get (i).getName ());
        }
    }
}
