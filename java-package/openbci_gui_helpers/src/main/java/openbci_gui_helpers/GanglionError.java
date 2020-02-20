package openbci_gui_helpers;

public class GanglionError extends Exception
{
    public String msg;
    /**
     * exit code returned from low level API
     */
    public int exit_code;

    public GanglionError (String message, int ec)
    {
        super (message + ":" + openbci_gui_helpers.GanglionExitCodes.string_from_code (ec));
        exit_code = ec;
        msg = message;
    }
}
