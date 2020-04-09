package openbci_gui_helpers;

import java.util.HashMap;
import java.util.Map;

public enum GanglionExitCodes
{

    STATUS_OK (0),
    PORT_OPEN_ERROR (1),
    GENERAL_ERROR (2),
    SYNC_ERROR (3);

    private final int exit_code;
    private static final Map<Integer, GanglionExitCodes> ec_map = new HashMap<Integer, GanglionExitCodes> ();

    public int get_code ()
    {
        return exit_code;
    }

    public static String string_from_code (final int code)
    {
        return from_code (code).name ();
    }

    public static GanglionExitCodes from_code (final int code)
    {
        final GanglionExitCodes element = ec_map.get (code);
        return element;
    }

    GanglionExitCodes (final int code)
    {
        exit_code = code;
    }

    static
    {
        for (final GanglionExitCodes ec : GanglionExitCodes.values ())
        {
            ec_map.put (ec.get_code (), ec);
        }
    }

}
