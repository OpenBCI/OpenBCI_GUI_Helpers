package openbci_gui_helpers;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.lang.reflect.Type;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.Map;
import java.util.stream.Collectors;

import org.apache.commons.lang3.SystemUtils;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.sun.jna.Library;
import com.sun.jna.Native;

public class GUIHelper
{
    private interface DllInterface extends Library
    {
        int scan_for_ganglions (String serial_port, int timeout_sec, byte[] output, int[] output_len);
    }

    private interface DllNativeInterface extends Library
    {
        int scan_for_ganglions (int timeout_sec, byte[] output, int[] output_len);
    }

    private static DllInterface instance;
    private static DllNativeInterface instance_native;

    static
    {
        String lib_name = "libGanglionScan.so";
        String lib_native_name = "libGanglionNativeScan.so";
        if (SystemUtils.IS_OS_WINDOWS)
        {
            lib_name = "GanglionScan.dll";
            lib_native_name = "GanglionNativeScan.dll";

        } else if (SystemUtils.IS_OS_MAC)
        {
            lib_name = "libGanglionScan.dylib";
            lib_native_name = "libGanglionNativeScan.dylib";
        }

        // need to extract libraries from jar
        String lib_path = unpack_from_jar (lib_name);
        String lib_native_path = unpack_from_jar (lib_native_name);

        instance = (DllInterface) Native.load (lib_path, DllInterface.class);
        instance_native = (DllNativeInterface) Native.load (lib_native_path, DllNativeInterface.class);
    }

    private static String unpack_from_jar (String lib_name)
    {
        try
        {
            File file = new File (lib_name);
            if (file.exists ())
                file.delete ();
            InputStream link = (GUIHelper.class.getResourceAsStream (lib_name));

            String text = new BufferedReader(
                new InputStreamReader(link, StandardCharsets.UTF_8))
                    .lines()
                    .collect(Collectors.joining("\n"));
            System.err.println("inputStream: " + text);
            System.err.println("file absolute path: " + file.getAbsoluteFile().toPath());

            Files.copy (link, file.getAbsoluteFile ().toPath ());
            return file.getAbsolutePath();
        } catch (Exception io)
        {
            System.err.println ("native library: " + lib_name + " is not found in jar file");
            return "";
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

    public static Map<String, String> scan_for_ganglions (int timeout_sec) throws GanglionError
    {
        int[] len = new int[1];
        byte[] output_json = new byte[10240];
        int ec = instance_native.scan_for_ganglions (timeout_sec, output_json, len);
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
