package openbci_gui_helpers.examples;

import java.io.IOException;
import java.util.List;

import com.vmichalak.protocol.ssdp.Device;
import com.vmichalak.protocol.ssdp.SSDPClient;

public class TestWifiDiscovery
{
    public static void main (String[] args) throws IOException
    {
        List<Device> devices = SSDPClient.discover (3000, "urn:schemas-upnp-org:device:Basic:1");
        System.out.println (devices.size () + " devices found");
    }
}
