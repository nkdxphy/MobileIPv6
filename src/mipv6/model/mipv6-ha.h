/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2017 Jadavpur University, India
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Manoj Kumar Rana <manoj24.rana@gmail.com>
 */

#ifndef MIPV6_HA_H
#define MIPV6_HA_H

#include "mipv6-agent.h"
#include "bcache.h"
#include "mipv6-header.h"

namespace ns3 {
class Packet;

class mipv6HA : public mipv6Agent
{
public:
  static TypeId GetTypeId (void);
  mipv6HA ();

  virtual ~mipv6HA ();
  std::list<Ipv6Address> HomeAgentAddressList ();
  void DoDADForOffLinkAddress (Ipv6Address target, Ptr<Ipv6Interface> interface);
  void FunctionDadTimeoutForOffLinkAddress (Ptr<Ipv6Interface> interface, Ptr<Packet> ba, Ipv6Address homeaddr);

  void DADFailureIndication (Ipv6Address addr);
  bool IsAddress (Ipv6Address addr);
  bool IsAddress2 (Ipv6Address addr);

  void HandleNS (Ptr<Packet> packet, Ptr<Ipv6Interface> interface, Ipv6Address src, Ipv6Address target);

  /**
   * TracedCallback signature for BU reception event.
   *
   * \param [in] packet The bu packet.
   * \param [in] src The source address
   * \param [in] dst The destination address
   * \param [in] interface the interface in which the bu received
   */
  typedef void (* RxBuTracedCallback)
    (Ptr<Packet> packet, Ipv6Address src, Ipv6Address dst, Ptr<Ipv6Interface> interface);

protected:
  virtual void NotifyNewAggregate ();

  Ptr<Packet> BuildBA (Ipv6MobilityBindingUpdateHeader bu,Ipv6Address hoa, uint8_t status);

  virtual uint8_t HandleBU (Ptr<Packet> packet, const Ipv6Address &src, const Ipv6Address &dst, Ptr<Ipv6Interface> interface);
  bool SetupTunnelAndRouting (BCache::Entry *bce);
  bool ClearTunnelAndRouting (BCache::Entry *bce);


private:
  Ptr<BCache> m_bCache;

  /**
   * \brief Callback to trace RX (reception) bu packets.
   */ 
  TracedCallback<Ptr<Packet>, Ipv6Address, Ipv6Address, Ptr<Ipv6Interface> > m_rxbuTrace;
};

} /* namespace ns3 */

#endif /* MIPV6_HA_H */

