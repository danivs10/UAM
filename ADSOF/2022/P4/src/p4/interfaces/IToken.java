package p4.interfaces;

public interface IToken {
    /**
     * Converts the token to a string
     * @return the string representation of the token
     */
    public String toString();
    /**
     * Gets if the token can be overwritten
     * @return
     */
    public boolean canBeOverwritten();
    }
    