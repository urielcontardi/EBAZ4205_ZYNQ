--! \file		blinky.vhd
--!
--! \brief		
--!
--! \author		Uriel Abe Contardi (contardii@weg.net)
--! \date       03-04-2024
--!
--! \version    1.0
--!
--! \copyright	Copyright (c) 2024 WEG - All Rights reserved.
--!
--! \note		Target devices : No specific target
--! \note		Tool versions  : No specific tool
--! \note		Dependencies   : No specific dependencies
--!
--! \ingroup	WCW
--! \warning	None
--!
--! \note		Revisions:
--!				- 1.0	03-04-2024	<contardii@weg.net>
--!				First revision.
--------------------------------------------------------------------------
-- Default libraries
--------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--------------------------------------------------------------------------
-- User packages
--------------------------------------------------------------------------

--------------------------------------------------------------------------
-- Entity declaration
--------------------------------------------------------------------------
Entity blinky is
    port (
        clk : in std_logic;
        led : out std_logic
    );
End blinky;

--------------------------------------------------------------------------
-- 
--------------------------------------------------------------------------
Architecture Behavioral of blinky is

    signal counter : unsigned(21 downto 0);

    type state is (LED_ON, LED_OFF);
    signal s : state;

Begin

    blinky : process (clk)
    begin
        if rising_edge(clk) then
            case s is
                when LED_ON =>
                    led <= '1';
                when LED_OFF =>
                    led <= '0';
            end case;

            if (counter >= 3000000) then
                if (s = LED_ON) then
                    s <= LED_OFF;
                else
                    s <= LED_ON;
                end if;
                counter <= to_unsigned(0, 22);
            else
                counter <= counter + 1;
            end if;
        end if;
    end process;
    
End Architecture;
