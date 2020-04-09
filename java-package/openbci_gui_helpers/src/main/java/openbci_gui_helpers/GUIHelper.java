package openbci_gui_helpers;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

import org.apache.commons.lang3.SystemUtils;

import com.sun.jna.Library;
import com.sun.jna.Native;

import java.lang.reflect.Type;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;

public class GUIHelper
{
    private interface DllInterface extends Library
    {
        int scan_for_ganglions (String serial_port, int timeout_sec, byte[] output, int[] output_len);
    }

    private static DllInterface instance;

    static
    {
        String lib_name = "libGanglionScan.so";
        if (SystemUtils.IS_OS_WINDOWS)
        {
            lib_name = "GanglionScan.dll";

        } else if (SystemUtils.IS_OS_MAC)
        {
            lib_name = "libGanglionScan.dylib";
        }

        // need to extract libraries from jar
        unpack_from_jar (lib_name);

        instance = (DllInterface) Native.loadLibrary (lib_name, DllInterface.class);
    }

    private static void unpack_from_jar (String lib_name)
    {
        try
        {
            File file = new File (lib_name);
            if (file.exists ())
                file.delete ();
            InputStream link = (GUIHelper.class.getResourceAsStream (lib_name));
            Files.copy (link, file.getAbsoluteFile ().toPath ());
        } catch (Exception io)
        {
            System.err.println ("native library: " + lib_name + " is not found in jar file");
        }
    }

    public static Map<String, String> scan_for_ganglions (String port_name, int timeout_sec) throws GanglionError
    {
        int[] len = new int[1];
        byte[] output_json = new byte[10240];
        int ec = instance.scan_for_ganglions (port_name, timeout_sec, output_json, len);
        if (ec != GanglionExitCodes.STATUS_OK.get_code ())
        {
            throw new GanglionError ("Error in scan for ganglions", ec);
        }
        String json = new String (output_json, 0, len[0]);
        Gson gson = new Gson ();
        Type type = new TypeToken<Map<String, String>> ()
        {
        }.getType ();
        Map<String, String> map = gson.fromJson (json, type);
        return map;
    }

}
