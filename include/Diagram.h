#pragma once

#include "QuarkLineBlock2.h"
#include "typedefs.h"

struct QuarkLineBlockCollection {
  QuarkLineBlock2<QuarkLineType::Q0> &q0;
  QuarkLineBlock2<QuarkLineType::Q1> &q1;
  QuarkLineBlock2<QuarkLineType::Q2> &q2l;
  QuarkLineBlock2<QuarkLineType::Q2> &q2v;

  DilutedTraceCollection<2> &corr0; 
  DilutedTraceCollection<2> &corrC; 
  DilutedTraceCollection2<1> &corr_part_trQ1;
};

class Diagram {
 public:
  Diagram(std::vector<CorrInfo> const &corr_lookup) : corr_lookup_(corr_lookup) {}

  virtual ~Diagram() {}

  void contract(std::vector<cmplx> &c,
                BlockIterator const &slice_pair,
                QuarkLineBlockCollection &q) {
    contract_impl(c, slice_pair, q);
  }

  virtual char const *name() const = 0;

  std::vector<CorrInfo> const &corr_lookup() const { return corr_lookup_; }

 private:
  virtual void contract_impl(std::vector<cmplx> &c,
                             BlockIterator const &slice_pair,
                             QuarkLineBlockCollection &q) = 0;

  std::vector<CorrInfo> const &corr_lookup_;
};

/*****************************************************************************/
/*                                    C3                                     */
/*****************************************************************************/

/*! Build neutral 3pt correlation function
 *  @f{align}{
 *    C = \langle \gamma_5 D_\mathtt{Q0}^{-1}(t|t)^\dagger \gamma_5 \Gamma_\mathtt{Op0}
 *                D_\mathtt{Q1}^{-1}(t|t') \Gamma_\mathtt{Op1}
 *                D_\mathtt{Q2}^{-1}(t'|t) \Gamma_\mathtt{Op2} \rangle
 *  @f}
 */
class C3c : public Diagram {
 public:
  C3c(std::vector<CorrInfo> const &corr_lookup);

  char const *name() const override { return "C3+"; }

 private:
  void contract_impl(std::vector<cmplx> &c,
                     BlockIterator const &slice_pair,
                     QuarkLineBlockCollection &q) override;

  std::vector<std::tuple<std::array<size_t, 2>, std::array<size_t, 1>>> quantum_num_ids_;
};

/*! Build neutral 3pt correlation function
 *  @f{align}{
 *    C = \langle D_\mathtt{Q0}^{-1}(t|t) \Gamma_\mathtt{Op0}
 *                D_\mathtt{Q1}^{-1}(t|t') \Gamma_\mathtt{Op1}
 *                D_\mathtt{Q2}^{-1}(t'|t) \Gamma_\mathtt{Op2} \rangle
 *  @f}
 */
class C30 : public Diagram {
 public:
  C30(std::vector<CorrInfo> const &corr_lookup);

  char const *name() const override { return "C30"; }

 private:
  void contract_impl(std::vector<cmplx> &c,
                     BlockIterator const &slice_pair,
                     QuarkLineBlockCollection &q) override;

  std::vector<std::tuple<std::array<size_t, 2>, std::array<size_t, 1>>> quantum_num_ids_;
};

/*****************************************************************************/
/*                                    C4                                     */
/*****************************************************************************/

/*! Build charged 4pt correlation function: Box diagram
 *  @f{align}{
 *    C = \langle \gamma_5 D_\mathtt{Q0}^{-1}(t|t)^\dagger \gamma_5 \Gamma_\mathtt{Op0}
 *                D_\mathtt{Q1}^{-1}(t|t') \Gamma_\mathtt{Op1}
 *                \gamma_5 D_\mathtt{Q2}^{-1}(t'|t')^\dagger \gamma_5 \Gamma_\mathtt{Op2}
 *                D_\mathtt{Q3}^{-1}(t'|t) \Gamma_\mathtt{Op3} \rangle
 *  @f}
 */
class C4cB : public Diagram {
 public:
  C4cB(std::vector<CorrInfo> const &corr_lookup);

  char const *name() const override { return "C4+B"; }

 private:
  void contract_impl(std::vector<cmplx> &c,
                     BlockIterator const &slice_pair,
                     QuarkLineBlockCollection &q) override;

  std::vector<std::array<std::array<size_t, 2>, 2>> quantum_num_ids_;
};

/*! Build neutral 4pt correlation function: Box diagram
 *  @f{align}{
 *    C = \langle D_\mathtt{Q0}^{-1}(t|t) \Gamma_\mathtt{Op0}
 *                D_\mathtt{Q1}^{-1}(t|t') \Gamma_\mathtt{Op1}
 *                D_\mathtt{Q2}^{-1}(t'|t') \Gamma_\mathtt{Op2}
 *                D_\mathtt{Q3}^{-1}(t'|t) \Gamma_\mathtt{Op3} \rangle
 *  @f}
 */
class C40B : public Diagram {
 public:
  C40B(std::vector<CorrInfo> const &corr_lookup);

  char const *name() const override { return "C40B"; }

 private:
  void contract_impl(std::vector<cmplx> &c,
                     BlockIterator const &slice_pair,
                     QuarkLineBlockCollection &q) override;

  std::vector<std::array<std::array<size_t, 2>, 2>> quantum_num_ids_;
};

/*! Build charged 4pt correlation function: Cross diagram
 *  @f{align}{
 *    C = \langle \gamma_5 D_\mathtt{Q0}^{-1}(t|t')^\dagger \gamma_5 \Gamma_\mathtt{Op0}
 *                D_\mathtt{Q1}^{-1}(t|t') \Gamma_\mathtt{Op1}
 *                \gamma_5 D_\mathtt{Q2}^{-1}(t|t')^\dagger \gamma_5 \Gamma_\mathtt{Op2}
 *                D_\mathtt{Q3}^{-1}(t|t') \Gamma_\mathtt{Op3} \rangle
 *  @f}
 */
class C4cC : public Diagram {
 public:
  C4cC(std::vector<CorrInfo> const &corr_lookup);

  char const *name() const override { return "C4+C"; }

 private:
  void contract_impl(std::vector<cmplx> &c,
                     BlockIterator const &slice_pair,
                     QuarkLineBlockCollection &q) override;

  std::vector<std::array<std::array<size_t, 2>, 2>> quantum_num_ids_;
};

/*! Build neutral 4pt correlation function: Cross diagram
 *  @f{align}{
 *    C = \langle D_\mathtt{Q0}^{-1}(t'|t) \Gamma_\mathtt{Op0}
 *                D_\mathtt{Q1}^{-1}(t|t') \Gamma_\mathtt{Op1}
 *                D_\mathtt{Q2}^{-1}(t'|t) \Gamma_\mathtt{Op2}
 *                D_\mathtt{Q3}^{-1}(t|t') \Gamma_\mathtt{Op3} \rangle
 *  @f}
 */
class C40C : public Diagram {
 public:
  C40C(std::vector<CorrInfo> const &corr_lookup);

  char const *name() const override { return "C40C"; }

 private:
  void contract_impl(std::vector<cmplx> &c,
                     BlockIterator const &slice_pair,
                     QuarkLineBlockCollection &q) override;

  std::vector<std::array<std::array<size_t, 2>, 2>> quantum_num_ids_;
};
