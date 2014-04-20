package mule.uni.ae.quicksort.util;

public class Args {
    private final String[] args;

    public Args(String[] args) {
        this.args = args;
    }

    public String get(String flag, String def) {
        return get(args, flag, def);
    }

    public int get(String flag, int def) {
        return get(args, flag, def);
    }

    public boolean get(String flag, boolean def) {
        return get(args, flag, def);
    }

    public static String get(String[] args, String flag, String def) {
        for (int i = 0; i < args.length - 1; i++) {
            if (args[i].equals(flag)) {
                return args[i+1];
            }
        }
        return def;
    }

    public static int get(String[] args, String flag, int def) {
        String value = get(args, flag, null);
        return (value != null) ? Integer.parseInt(value) : def;
    }

    public static boolean get(String[] args, String flag, boolean def) {
        for (String arg : args) {
            if (arg.equals(flag)) {
                return true;
            }
        }
        return def;
    }
}
